#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "./../libft/libft.h"
# include <curses.h>
# include <term.h>
# include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

typedef struct		s_liste
{
	char		*name_node;
	int		act;
	struct s_liste	*next;
}			t_liste;

typedef struct		s_env
{
	char		*type_term;
	char		*slg;
	char		*csr;
	char		*cln;
	char		*rst;
	char		*bgc;
	char		*txt;
	char		tch[3];
	int		csr_term;
	int		nb_arg;
	struct termios	tc;
	struct s_liste	*first;
}			t_env;

void			ft_init_liste(t_env *env, char **argv);
void			ft_init_termcap(t_env *env);
void			ft_init_prog(t_env *env);
void			ft_reset_term(t_env *env);
void			ft_run(t_env *env);
void			ft_first(t_env *env);
void			ft_bgc_txt(t_env *env);
void			ft_press_space(t_env *env, t_liste *liste);

#endif
