/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:57 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/22 14:17:03 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

t_env		*env2;

void		ft_signal_window(int sig)
{
	if (sig == SIGWINCH)
	{
		env2->row = 0;
		env2->col = 0;
		ioctl(0, TIOCGWINSZ, env2->wsize);
		ft_init_calc_write(env2);
		tputs(env2->cln, 1, ft_putchar);
		tputs(tgoto(env2->csr, env2->row, env2->col), 1, ft_putchar);
		ft_show(env2);
	}
}

void		ft_signal_cont(int sig)
{
	if (sig == SIGCONT)
	{
		env2->row = 0;
		env2->col = 0;
		ioctl(0, TIOCGWINSZ, env2->wsize);
		ft_init_calc_write(env2);
		ft_init_termcap(env2);
		ft_init_prog(env2);
		ft_show(env2);
		ft_run(env2);
	}
}

void		ft_signal_kill(int sig)
{
	(void)sig;
	ft_reset_term(env2);
	exit(1);
}

void		ft_signal(void)
{
	if (signal(SIGWINCH, ft_signal_window) == SIG_ERR)
		;
	if (signal(SIGCONT, ft_signal_cont) == SIG_ERR)
		;
	if (signal(SIGINT, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGFPE, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGSEGV, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGSEGV, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGABRT, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGPIPE, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGALRM, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGTERM, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGUSR1, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGUSR2, ft_signal_kill) == SIG_ERR)
		;
}

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
	{
		ft_putendl("usage: ft_select name1 [name2 ...]");
		return (0);
	}
	env.row = 0;
	env.col = 0;
	env.csr_term = 0;
	env2 = &env;
	env.nb_arg = argc - 2;
	ft_signal();
	ft_init_liste(&env, argv);
	ft_init_termcap(&env);
	ft_size_word_max(&env);
	ioctl(0, TIOCGWINSZ, &env.wsize);
	ft_init_calc_write(&env);
	ft_init_prog(&env);
	ft_bzero(env.tch, 3);
	ft_run(&env);
	return (0);
}
