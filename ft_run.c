#include "./includes/ft_select.h"

static void	ft_press_space(t_env *env, t_liste *liste)
{
	if (env->tch[0] == 32)
	{
		if (liste->act)
			liste->act = 0;
		else
			liste->act = 1;
	}
}

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
	int	i;

	i = 0;
	liste = env->first->next;
	ft_first(env);
	while (liste != env->first)
	{
		if (env->csr_term == ++i)
		{
			tputs(env->slg, 1, ft_putchar);
			ft_press_space(env, liste);
		}
		if (liste->act)
			ft_bgc_txt(env);
		ft_putendl(liste->name_node);
		tputs(env->rst, 1, ft_putchar);
		liste = liste->next;
	}
}

static void	ft_if_tch(t_env *env)
{
	if (env->tch[0] == 10 || (env->tch[0] == 27 && env->tch[1] == 0))
	{
		ft_reset_term(env);
		exit(0);
	}
	else if (env->tch[0] == 127 && env->tch[1] == 0 && !env->first->next)
	{
		ft_reset_term(env);
		exit(0);
	}
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 66)
		env->csr_term++;
	else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 65)
		env->csr_term--;
	if (env->csr_term >= env->nb_arg)
		env->csr_term = 0;
	else if (env->csr_term < 0)
		env->csr_term = env->nb_arg - 1;
}

void		ft_run(t_env *env)
{
	int	ret;

	env->csr_term = 0;
	while (42)
	{
		if ((ret = read(0, env->tch, 3)) <= 0)
			break;
		ft_if_tch(env);
		tputs(env->cln, 1, ft_putchar);
		tputs(tgoto(env->csr, 0, 0), 1, ft_putchar);
		ft_search_node(env, env->first);
		ft_show(env);
		printf("tch = %d %d %d\n", env->tch[0], env->tch[1], env->tch[2]);
		tputs(env->rst, 1, ft_putchar);
		ft_bzero(env->tch, 3);
	}
	ft_show_selection(env);
	ft_reset_term(env);
}
