#include "./includes/ft_select.h"

static void	ft_show_selection(t_env *env)
{
	t_liste	*liste;

	liste = env->first->next;
	if (env->first->act)
		ft_putendl(env->first->name_node);
	while (liste != env->first)
	{
		if (liste->act)
			ft_putendl(liste->name_node);
		liste = liste->next;
	}
}

static void	ft_show(t_env *env)
{
	t_liste	*liste;
	int		i;

	i = 1;
	ft_first(env);
	liste = env->first->next;
	while (liste != env->first)
	{
//		printf("csr = %d i = %d nb = %d\n", env->csr_term, i, env->nb_arg);
		if (env->csr_term == i++)
		{
			if (env->tch[0] == 127)
			{
				env->nb_arg--;
				ft_press_delete_or_backs(env, liste);
				liste = liste->next;
			}
			tputs(env->slg, 1, ft_putchar);
			ft_press_space(env, liste);
		}
		if (liste->act)
			ft_bgc_txt(env);
		if (liste != env->first)
		{
			ft_putendl(liste->name_node);
			liste = liste->next;
		}
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
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 66)
		env->csr_term++;
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 65)
		env->csr_term--;
	if (env->csr_term > env->nb_arg)
		env->csr_term = 0;
	else if (env->csr_term < 0)
		env->csr_term = env->nb_arg;
}

void		ft_run(t_env *env)
{
	int	ret;

	env->csr_term = 0;
	while (42)
	{
		ioctl(0, TIOCGWINSZ, &env->wsize);
		if ((ret = read(0, env->tch, 3)) < 0)
			break;
		if (ret)
		{
//			printf("row = %d col = %d %d\n", env->wsize.ws_row, env->wsize.ws_col, ttyslot());
//			printf("csr = %d nb = %d\n", env->csr_term, env->nb_arg);
//			sleep(1);
//		printf("tch = %d %d %d\n", env->tch[0], env->tch[1], env->tch[2]);
			ft_if_tch(env);
			tputs(env->cln, 1, ft_putchar);
			tputs(tgoto(env->csr, 0, 0), 1, ft_putchar);
			ft_show(env);
			tputs(env->rst, 1, ft_putchar);
			ft_bzero(env->tch, 3);
		}
	}
	ft_show_selection(env);
	ft_reset_term(env);
}
