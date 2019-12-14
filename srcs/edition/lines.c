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

void count_ret(t_var *data, int pos)
{
  int i;

  i = pos;
//  ft_printf("\n|%s|\n", data->lex_str);
  if (!data->lex_str[0])
    return ;
  while (i > 0)
  {
    if (data->lex_str[i] == '\n')
      data->nb_ret++;
    i--;
  }
  if (data->mod_ret == 1)
    data->nb_ret++;
}

int  how_many_before(t_var *data, int pos)
{
  int i;

  i = pos - 1;
  while (i > 0 && data->lex_str[i] != '\n')
    i--;
  return (i);
}


int   count_current_ret(t_var *data)
{
  int i;
  int current;

  current = 0;
  i = data->pos;
  while (i > 0)
    if (data->lex_str[i--] == '\n')
      current++;
  if (data->mod_ret == 1)
    current++;
  return (current);
}
/*int  pos_lex(t_var *data)
{
  int i;

  i = 0;
  while (data->lex_str)
}*/
