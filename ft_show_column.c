/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_column.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 11:14:46 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/23 17:01:27 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

static void			ft_color_file(char *av)
{
	struct stat		s;

	if (stat(av, &s) == -1)
		ft_putendl_fd(av, 2);
	else if (S_ISLNK(s.st_mode))
		ft_printf("{magenta}%s{eoc}{fd}2\n", av);
	else if (S_ISDIR(s.st_mode))
		ft_printf("{cyan}%s{eoc}{fd}2\n", av);
	else if (S_ISCHR(s.st_mode))
		ft_printf("{green}%s{eoc}{fd}2\n", av);
	else if (S_ISBLK(s.st_mode))
		ft_printf("{blue}%s{eoc}{fd}2\n", av);
	else if (S_ISFIFO(s.st_mode))
		ft_printf("{blue}%s{eoc}{fd}2\n", av);
	else if (S_ISSOCK(s.st_mode))
		ft_printf("{yellow}%s{eoc}{fd}2\n", av);
	else if (s.st_mode & S_IXUSR)
		ft_printf("{red}%s{eoc}{fd}2\n", av);
	else
		ft_putendl_fd(av, 2);
}

void				ft_show_column2(t_env *env, char *name_node)
{
	if (env->nb_arg >= env->div && env->col < env->nb_arg / env->div)
	{
		tputs(tgoto(env->csr, env->row, env->col), 1, ft_putchar);
		ft_color_file(name_node);
		env->col++;
	}
	else
	{
		tputs(tgoto(env->csr, env->row, env->col), 1, ft_putchar);
		ft_color_file(name_node);
		env->row += env->size_word_max + 3;
		env->col = 0;
	}
}

void				ft_show_column(t_env *env, char *name_node)
{
	if (env->res < 0 || env->wsize.ws_col - env->size_word_max - 2 < 0 ||
			     env->wsize.ws_row < env->nb_arg / env->div + 2)
		return ;
	if (env->res >= env->wsize.ws_col / 2)
	{
		tputs(tgoto(env->csr, env->row, env->col), 1, ft_putchar);
		ft_color_file(name_node);
		env->col++;
		return ;
	}
	ft_show_column2(env, name_node);
}
