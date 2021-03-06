/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:49 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/07 15:21:47 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

void		ft_first(t_env *env)
{
	if (env->tch[0] == 127 && env->tch[1] == 0 && env->csr_term == 0)
	{
		ft_press_delete_or_backs(env, env->first);
		env->nb_arg--;
	}
	if (env->csr_term == 0)
		ft_press_space(env, env->first);
	if (env->first->act)
		ft_bgc_txt(env);
	ft_show_column(env, env->first->name_node);
	tputs(env->rst, 1, ft_putchar);
}

void		ft_bgc_txt(t_env *env)
{
	tputs(env->bgc, 1, ft_putchar);
}

void		ft_press_space(t_env *env, t_liste *liste)
{
	if (env->tch[0] == 32)
	{
		if (liste->act)
		{
			tputs(env->slg, 1, ft_putchar);
			liste->act = 0;
		}
		else
		{
			liste->act = 1;
			env->csr_term++;
			ft_bzero(env->tch, 3);
		}
	}
	else
		tputs(env->slg, 1, ft_putchar);
}

void		ft_press_delete_or_backs(t_env *env, t_liste *liste)
{
	int	i;

	i = 0;
	if (env->first == env->last)
	{
		ft_reset_term(env);
		tputs(env->cln, 1, ft_putchar);
		exit(0);
	}
	while (i < env->csr_term)
	{
		liste = liste->next;
		i++;
	}
	if (env->csr_term < 0)
		env->csr_term = 0;
	else if (env->csr_term > env->nb_arg)
		env->csr_term = env->nb_arg;
	ft_search_node(env, liste);
	tputs(env->rst, 1, ft_putchar);
	ft_bzero(env->tch, 3);
}

void		ft_size_word_max(t_env *env)
{
	t_liste	*liste;

	liste = env->first->next;
	env->size_word_max = ft_strlen(env->first->name_node);
	while (liste != env->first)
	{
		if (env->size_word_max < (int)ft_strlen(liste->name_node))
			env->size_word_max = ft_strlen(liste->name_node);
		liste = liste->next;
	}
}
