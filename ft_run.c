/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:42 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/26 16:28:56 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

static void	ft_show_selection(t_env *env)
{
	t_liste	*liste;

	liste = env->first->next;
	if (env->first->act)
	{
		ft_putstr_fd(env->first->name_node, 1);
		ft_putstr_fd(" ", 1);
	}
	while (liste != env->first)
	{
		if (liste->act)
		{
			ft_putstr_fd(liste->name_node, 1);
			ft_putstr_fd(" ", 1);
		}
		liste = liste->next;
	}
	ft_putstr_fd("\n", 1);
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
			ft_press_space(env, liste);
		ft_show2(env, &liste);
		tputs(env->rst, 1, ft_putchar);
	}
}

static void	ft_if_tch(t_env *env)
{
	if (env->tch[0] == 10 || (env->tch[0] == 27 && env->tch[1] == 0))
	{
		ft_reset_term(env);
		if (env->tch[0] == 10)
			ft_show_selection(env);
		exit(0);
	}
	else if (env->tch[0] == 127)
	{
		env->nb_arg--;
		ft_press_delete_or_backs(env, env->first);
	}
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 66)
		env->csr_term++;
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 65)
		env->csr_term--;
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 67)
		env->csr_term += env->nb_arg / env->div + 1;
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 68)
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
		signal(SIGTSTP, ft_signal_tstp);
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
			tputs(tgoto(env->csr, env->row, env->col), 2, ft_putchar);
			ft_show(env);
			tputs(env->rst, 1, ft_putchar);
			ft_bzero(env->tch, 3);
		}
	}
	ft_show_selection(env);
	ft_reset_term(env);
}
