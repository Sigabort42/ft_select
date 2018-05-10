/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_column.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 11:14:46 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/09 13:53:10 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

void		ft_show_column2(t_env *env, char *name_node)
{
//	printf("ici = %d %d\n", env->nb_arg, env->div);
//	sleep(1);
	if (env->nb_arg >= env->div && env->col < env->nb_arg / env->div)
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

	ft_size_word_max(env);
	env->div = 3;
	res = env->wsize.ws_col - (env->wsize.ws_col - env->size_word_max);
	if (res < 0  || env->wsize.ws_col - env->size_word_max - 2 < 0)
	{
//		ft_putendl("the window size is shortly");
		return ;
	}
	if (res >= env->wsize.ws_col / 2)
	{
		tputs(tgoto(env->csr, env->row, env->col), 1, ft_putchar);
		ft_putendl(name_node);
		env->col++;
		return ;
	}
	while (res * env->div < env->wsize.ws_col - 20)
		env->div++;
//	env->div--;
//	printf("lolol col = %d row = %d res = %d div = %d\n", env->wsize.ws_col, env->wsize.ws_row, res, env->div);
//	sleep(1);
	ft_show_column2(env, name_node);
}
