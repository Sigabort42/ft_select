/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_column.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 11:14:46 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/07 13:36:57 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

void		ft_show_column2(t_env *env, char *name_node)
{
	if (env->col < env->nb_arg / env->div - 1)
	{
		tputs(tgoto(env->csr, env->row, env->col), 1, ft_putchar);
		ft_putendl(name_node);
		env->col++;
	}
	else
	{
		tputs(tgoto(env->csr, env->row, env->col), 1, ft_putchar);
		ft_putendl(name_node);
		env->row += env->size_word_max + 3;
		env->col = 0;
	}
}

void		ft_show_column(t_env *env, char *name_node)
{
	int		res;

	env->div = 3;
	res = env->wsize.ws_col - env->size_word_max - 5;
	if (res < 0)
	{
		ft_putendl("the window size is shortly");
		return ;
	}
	if (res <= env->wsize.ws_col / 2)
	{
		tputs(tgoto(env->csr, env->row, env->col), 1, ft_putchar);
		ft_putendl(name_node);
		env->col++;
		return ;
	}
	while (res <= env->wsize.ws_col / env->div)
		env->div++;
	ft_show_column2(env, name_node);
//	printf("ici = %d %d %d\n", res, env->wsize.ws_col / env->div, env->nb_arg / env->div);
//	sleep(1);
}
