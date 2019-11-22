/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:13:28 by jebrocho          #+#    #+#             */
/*   Updated: 2019/11/08 13:13:43 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void count_ret(t_var *data)
{
  int i;

  i = -1;
//  ft_printf("\n|%s|\n", data->lex_str);
  if (!data->lex_str[0])
    return ;
  while (data->lex_str[++i])
    if (data->lex_str[i] == '\n')
      data->nb_ret++;
}

int  count_char_line(t_var *data)
{
  int i;

  i = 0;
  while (data->lex_str[i] != '\n')
    i++;
  return (i);
}

/*int  pos_lex(t_var *data)
{
  int i;

  i = 0;
  while (data->lex_str)
}*/
