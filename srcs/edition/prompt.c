/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:47:01 by ezonda            #+#    #+#             */
/*   Updated: 2019/12/10 07:11:28 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void		print_str(t_var *data)
{
	int i;

	i = 0;
	while (data->lex_str[i])
	{
		if (data->tab[i] == 0)
			ft_putchar(data->lex_str[i]);
		else
		{
			TERMCAP("mr");
			ft_putchar(data->lex_str[i]);
			TERMCAP("me");
		}
		i++;
	}
}

static void 	print_tronc_str(t_var *data)
{
	int i;

	i = ft_strlen(data->lex_str);
	while (data->lex_str[i] != '\n' && i > 0)
		i--;
	i++;
	while (data->lex_str[i])
	{
		if (data->tab[i] == 0)
			ft_putchar(data->lex_str[i]);
		else
		{
			TERMCAP("mr");
			ft_putchar(data->lex_str[i]);
			TERMCAP("me");
		}
		i++;
	}
}

static void		print_prompt(t_var *data)
{
	if (data->quotes % 2 != 0 || data->dquotes % 2 != 0)
	{
		data->std_prompt = 0;
		ft_putstr("quotes> ");
	}
	else if (data->p_prompt == 1)
		ft_putstr("pipe> ");
	else if (data->h_prompt == 1)
		ft_putstr("heredoc> ");
	else if (data->n_prompt == 1)
		ft_putstr("> ");
	else if (data->c_prompt == 1)
		ft_putstr("cursh> ");
	else
	{
		TERMCAP("md");
		data->std_prompt = 1;
		ft_putstr("21sh $> ");
		TERMCAP("me");
	}
}

void			prompt(t_var *data)
{
	int tmp;
	int current_ret;

	current_ret = count_current_ret(data);
	tmp = data->pos;
	if (data->p_prompt != 1)
		data->pos = -9;
	else if (data->p_prompt == 1)
		data->pos = -7;
	else if (data->h_prompt == 1)
		data->pos = -10;
	else if (data->n_prompt == 1)
		data->pos = -3;
	else if (data->c_prompt == 1)
		data->pos = -8;
	if (data->mod_pos != 1)
	{
		get_curs_pos(data, data->pos);
		if (data->quotes % 2 == 0 && data->dquotes % 2 == 0 && data->mod_lines != 0)
		{
			count_ret(data, tmp);
			data->mod_ret = 0;
			while (data->nb_ret > 0)
			{
				data->nb_ret--;
				TERMCAP("up");
			}
		}
		data->mod_lines = 1;
	}
	else
		get_curs_pos_line(data, current_ret);
	TERMCAP("cd");
	print_prompt(data);
	if (data->quotes % 2 == 0 && data->dquotes % 2 == 0)
		print_str(data);
	else
		print_tronc_str(data);
	data->pos = tmp;
	pos_curs_line(data);
}

void			get_winsize(t_var *data)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &wind);
	data->nb_cols = wind.ws_col - 8;
	data->nb_rows = wind.ws_row;
}

void pos_curs_line(t_var *data)
{
	int index;
	int first_pos;
	int current_ret;
	int nb_prompt;

	index = ft_strlen(data->lex_str);
	while (index > data->pos)
	{
		if (data->lex_str[index] == '\n')
		{
			first_pos = how_many_before(data, index);
			current_ret = count_current_ret(data);
			if (current_ret == 0)
				nb_prompt = -9;
			else
				nb_prompt = 0;
			TERMCAP("up");
			while (nb_prompt < 0)
			{
				TERMCAP("nd");
				nb_prompt++;
 			}
			if (current_ret == 0)
				first_pos = 0;
			while (first_pos < index - 1)
			{
				TERMCAP("nd");
				first_pos++;
			}
			index--;
		}
		else
		{
			TERMCAP("le");
			index--;
		}
	}
	data->mod_pos = 0;
}

void 			get_curs_pos_line(t_var *data, int current_ret)
{
	int index;

	index = 0;
	while (data->lex_str[index] != '\n')
		index++;
	while (current_ret > 0)
	{
		TERMCAP("up");
		current_ret--;
	}
	while (index > data->pos)
	{
		TERMCAP("le");
		index--;
	}
	data->mod_pos = 2;
}

void			get_curs_pos(t_var *data, int index)
{
	index = ft_strlen(data->lex_str);
	while (index > data->pos)
	{
		TERMCAP("le");
		index--;
	}
}
