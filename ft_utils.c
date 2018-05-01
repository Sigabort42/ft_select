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
