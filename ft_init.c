/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:20 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/26 16:38:37 by elbenkri         ###   ########.fr       */
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
	liste->act = 0;
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
	if (tgetent(0, env->type_term) == ERR ||
	ft_strcmp(env->type_term, "xterm-256color"))
	{
		env->type_term = ft_strdup("xterm-256color");
		if (tgetent(0, env->type_term) == ERR)
		{
			ft_putendl("Probleme d'environnement");
			exit(1);
		}
	}
	env->slg = tgetstr("us", 0);
	env->csr = tgetstr("cm", 0);
	env->cln = tgetstr("cl", 0);
	env->rst = tgetstr("me", 0);
	env->bgc = tgetstr("mr", 0);
	if (env->slg == 0 || env->csr == 0 || env->cln == 0 || env->rst == 0 ||
	env->bgc == 0)
		exit(1);
	tputs(tgetstr("ti", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
}

void		ft_reset_term(t_env *env)
{
	env->tc.c_lflag |= (ICANON | ECHO);
	tputs(tgetstr("te", NULL), 1, ft_putchar);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	tcsetattr(0, 0, &env->tc);
}

void		ft_init_prog(t_env *env)
{
	tputs(env->cln, 1, ft_putchar);
	tputs(tgoto(env->csr, 0, 0), 1, ft_putchar);
	ft_show(env);
	tcgetattr(0, &env->tc);
	env->tc.c_lflag &= ~(ICANON | ECHO);
	env->tc.c_cc[VMIN] = 0;
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
