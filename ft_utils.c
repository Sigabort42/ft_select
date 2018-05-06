#include "./includes/ft_select.h"

void		ft_first(t_env *env)
{
	if (env->tch[0] == 127 && env->tch[1] == 0 && env->csr_term == 0)
	{
		ft_press_delete_or_backs(env, env->first);
		env->nb_arg--;
	}
	if (env->first->act)
		ft_bgc_txt(env);
	if (env->csr_term == 0)
	{
		tputs(env->slg, 1, ft_putchar);
		ft_press_space(env, env->first);
	}
	ft_putendl(env->first->name_node);
	tputs(env->rst, 1, ft_putchar);
}

void		ft_bgc_txt(t_env *env)
{
	tputs(tparm(env->bgc, COLOR_WHITE), 1, ft_putchar);
	tputs(tparm(env->txt, COLOR_BLACK), 1, ft_putchar);
}

void		ft_press_space(t_env *env, t_liste *liste)
{
	if (env->tch[0] == 32)
	{
		if (liste->act)
			liste->act = 0;
		else
			liste->act = 1;
	}
}

void		ft_press_delete_or_backs(t_env *env, t_liste *liste)
{
	if (env->first == env->last)
	{
		ft_reset_term(env);
		exit(0);
	}
	if (env->csr_term < 0)
		env->csr_term = 0;
	else if (env->csr_term > env->nb_arg)
		env->csr_term = env->nb_arg;
	ft_search_node(env, liste);
	tputs(env->rst, 1, ft_putchar);
	ft_bzero(env->tch, 3);
}
