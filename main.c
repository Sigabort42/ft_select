/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:50:57 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/26 18:52:39 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_select.h"

static void	ft_signal_window(int sig)
{
	if (sig == SIGWINCH)
	{
		g_env2->row = 0;
		g_env2->col = 0;
		ioctl(0, TIOCGWINSZ, g_env2->wsize);
		ft_init_calc_write(g_env2);
		tputs(g_env2->cln, 1, ft_putchar);
		tputs(tgoto(g_env2->csr, g_env2->row, g_env2->col), 1, ft_putchar);
		ft_show(g_env2);
	}
}

static void	ft_signal_cont(int sig)
{
	if (sig == SIGCONT)
	{
		g_env2->row = 0;
		g_env2->col = 0;
		ioctl(0, TIOCGWINSZ, g_env2->wsize);
		ft_init_calc_write(g_env2);
		ft_init_termcap(g_env2);
		ft_init_prog(g_env2);
		ft_show(g_env2);
	}
}

static void	ft_signal_kill(int sig)
{
	(void)sig;
	ft_reset_term(g_env2);
	exit(1);
}

static void	ft_signal(void)
{
	if (signal(SIGWINCH, ft_signal_window) == SIG_ERR)
		;
	if (signal(SIGTSTP, ft_signal_tstp) == SIG_ERR)
		;
	if (signal(SIGCONT, ft_signal_cont) == SIG_ERR)
		;
	if (signal(SIGKILL, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGINT, ft_signal_kill) == SIG_ERR)
		;
	if (signal(SIGFPE, ft_signal_kill) == SIG_ERR)
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
	g_env2 = &env;
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
