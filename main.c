/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:57 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/06 09:50:57 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
	{
		ft_putendl("usage: ft_select name1 [name2 ...]");
		return (0);
	}
	env.nb_arg = argc - 2;
	ft_init_liste(&env, argv);
	ft_init_termcap(&env);
	ft_init_prog(&env);
	ft_bzero(env.tch, 3);
	ft_run(&env);
	return (0);
}
