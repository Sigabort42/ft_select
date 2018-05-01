#include "./includes/ft_select.h"

static void	ft_bgc_txt(t_env *env)
{
	tputs(tparm(env->bgc, COLOR_WHITE), 1, ft_putchar);
	tputs(tparm(env->txt, COLOR_BLACK), 1, ft_putchar);
}

static void	ft_show(t_env *env)
{
	t_liste	*liste;
	int	i;

	liste = env->first->next;
	i = 0;
	if (env->first->act)
		ft_bgc_txt(env);
	ft_putendl(env->first->name_node);
	while (liste != env->first)
	{
		if (env->csr_term == i)
		{
			ft_bgc_txt(env);
			if (env->tch[0] == 32)
			{
				if (liste->act)
					liste->act = 0;
				else
					liste->act = 1;
			}
		}
		if (liste->act)
			tputs(env->slg, 1, ft_putchar);
		ft_putendl(liste->name_node);
		tputs(env->rst, 1, ft_putchar);
		liste = liste->next;
		i++;
	}
}

void		ft_run(t_env *env)
{
	int	ret;

	env->csr_term = 0;
	while (42)
	{
		if ((ret = read(0, env->tch, 3)) <= 0)
			break;
		if (env->tch[0] == 10)
			break;
		else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 66)
			env->csr_term++;
		else if (env->tch[0] == 27 && env->tch[1] == 91 && env->tch[2] == 65)
			env->csr_term++;
		if (env->csr_term >= env->nb_arg)
			env->csr_term = 0;
		else if (env->csr_term < 0)
			env->csr_term = env->nb_arg;			
		tputs(env->cln, 1, ft_putchar);
		tputs(tgoto(env->csr, 0, 0), 1, ft_putchar);
		ft_show(env);
		tputs(env->rst, 1, ft_putchar);
		ft_bzero(env->tch, 3);
	}
	ft_reset_term(env);
}