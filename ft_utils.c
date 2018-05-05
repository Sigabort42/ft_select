#include "./includes/ft_select.h"

void		ft_first(t_env *env)
{
	if (env->csr_term == 0)
	{
		tputs(env->slg, 1, ft_putchar);
		ft_press_space(env, env->first);
	}
	if (env->first->act)
		ft_bgc_txt(env);
	ft_putendl(env->first->name_node);
	tputs(env->rst, 1, ft_putchar);
}

void		ft_bgc_txt(t_env *env)
{
	tputs(tparm(env->bgc, COLOR_WHITE), 1, ft_putchar);
	tputs(tparm(env->txt, COLOR_BLACK), 1, ft_putchar);
}
