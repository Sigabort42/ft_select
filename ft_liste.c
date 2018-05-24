/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:33 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/23 17:12:28 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

static void		ft_exit_prog(t_env *env)
{
	if (!ft_count_liste(env->first))
	{
		ft_reset_term(env);
		tputs(env->cln, 1, ft_putchar);
		tputs(tgoto(env->csr, 0, 0), 1, ft_putchar);
		exit(1);
	}
}

void		ft_search_node(t_env *env, t_liste *node)
{
	t_liste	*search;

	search = env->first->next;
	if (env->first == node)
	{
		free(node);
		env->first = 0;
		env->first = search;
		env->last->next = search;
		ft_exit_prog(env);
		return ;
	}
	while (search->next && search->next != node)
		search = search->next;
	if (search->next == node)
	{
		if (env->last == node)
			env->last = search;
		search->next = node->next;
		free(node);
		node = 0;
	}
}

int			ft_count_liste(t_liste *first)
{
	int		i;
	t_liste *liste;

	i = 0;
	liste = first->next;
	if (first)
		i++;
	while (liste != first)
	{
		i++;
		liste = liste->next;
	}
	return (i);
}
