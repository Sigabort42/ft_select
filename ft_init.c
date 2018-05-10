/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:20 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/07 17:26:22 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

void		ft_init_liste(t_env *env, char **argv)
{
	t_liste *liste;
	int		i;

	i = 2;
	liste = (t_liste*)malloc(sizeof(t_liste));
	liste->name_node = argv[1];
	env->first = liste;
	while (argv[i])
	{
		liste->next = (t_liste*)malloc(sizeof(t_liste));
		liste = liste->next;
		liste->name_node = argv[i++];
		liste->act = 0;
	}
	env->last = liste;
	liste->next = env->first;
}

void		ft_init_termcap(t_env *env)
{
	env->type_term = getenv("TERM");
	if (tgetent(0, env->type_term) == ERR)
	{
		ft_putendl("Probleme d'environnement");
		exit(1);
	}
	env->slg = tgetstr("us", 0);
	env->csr = tgetstr("cm", 0);
	env->cln = tgetstr("cl", 0);
	env->rst = tgetstr("me", 0);
	env->bgc = tgetstr("AB", 0);
	env->txt = tgetstr("AF", 0);
}

void		ft_reset_term(t_env *env)
{
	env->tc.c_lflag = (ICANON | ECHO);
	tcsetattr(0, 0, &env->tc);
}

void		ft_init_prog(t_env *env)
{
	t_liste *liste;

	liste = env->first->next;
	tputs(env->cln, 1, ft_putchar);
	tputs(tgoto(env->csr, 0, 0), 1, ft_putchar);
	tputs(env->slg, 1, ft_putchar);
	ft_show_column(env, env->first->name_node);
	tputs(env->rst, 1, ft_putchar);
	while (liste != env->first)
	{
		ft_show_column(env, liste->name_node);
		liste = liste->next;
	}
	tcgetattr(0, &env->tc);
	env->tc.c_lflag = ~(ICANON | ECHO);
	env->tc.c_cc[VMIN] = 1;
	env->tc.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &env->tc);
	tputs(tgoto(env->csr, 0, 0), 1, ft_putchar);
	env->row = 0;
	env->col = 0;
}

void		ft_init_calc_write(t_env *env)
{
	env->div = 1;
	env->res = env->wsize.ws_col - (env->wsize.ws_col - env->size_word_max);
	while (env->res * env->div < env->wsize.ws_col - 20)
		env->div++;
}
