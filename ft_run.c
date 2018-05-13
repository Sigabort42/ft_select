/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:42 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/09 13:38:46 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

static void	ft_show_selection(t_env *env)
{
	t_liste	*liste;

	liste = env->first->next;
	tputs(env->cln, 1, ft_putchar);
	tputs(tgoto(env->csr, 0, 0), 1, ft_putchar);
	if (env->first->act)
	{
		ft_putstr(env->first->name_node);
		ft_putstr(" ");
	}
	while (liste != env->first)
	{
		if (liste->act)
		{
			ft_putstr(liste->name_node);
			ft_putstr(" ");
		}
		liste = liste->next;
	}
	ft_putstr("\b\n");
}

static void	ft_show2(t_env *env, t_liste **liste)
{
	if ((*liste)->act)
		ft_bgc_txt(env);
	if (*liste != env->first)
	{
		ft_show_column(env, (*liste)->name_node);
		*liste = (*liste)->next;
	}
}

void		ft_show(t_env *env)
{
	t_liste	*liste;
	int		i;

	i = 1;
	ft_first(env);
	liste = env->first->next;
	while (liste != env->first)
	{
		if (env->csr_term == i++)
		{
			if (env->tch[0] == 127)
			{
				env->nb_arg--;
				ft_press_delete_or_backs(env, liste);
				liste = liste->next;
			}
			ft_press_space(env, liste);
		}
		ft_show2(env, &liste);
		tputs(env->rst, 1, ft_putchar);
	}
}

static void	ft_if_tch(t_env *env)
{
	if (env->tch[0] == 10 || (env->tch[0] == 27 && env->tch[1] == 0))
	{
		ft_reset_term(env);
		ft_show_selection(env);
		exit(0);
	}
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 66) //bottom
		env->csr_term++;
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 65) //top
		env->csr_term--;
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 67) //right
		env->csr_term += env->nb_arg / env->div + 1;
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 68) //left
		env->csr_term -= env->nb_arg / env->div + 1;
	if (env->csr_term > env->nb_arg)
		env->csr_term = 0;
	else if (env->csr_term < 0)
		env->csr_term = env->nb_arg;
}

void		ft_run(t_env *env)
{
	int	ret;

	while (42)
	{
		ioctl(0, TIOCGWINSZ, &env->wsize);
		if ((ret = read(0, env->tch, 3)) < 0)
			break ;
		ft_init_calc_write(env);
		if (ret)
		{
			env->row = 0;
			env->col = 0;
			ft_if_tch(env);
			tputs(env->cln, 1, ft_putchar);
			tputs(tgoto(env->csr, env->row, env->col), 1, ft_putchar);
			ft_show(env);
			tputs(env->rst, 1, ft_putchar);
			ft_bzero(env->tch, 3);
		}
	}
	ft_show_selection(env);
	ft_reset_term(env);
}
