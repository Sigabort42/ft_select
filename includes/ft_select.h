/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 09:51:04 by elbenkri          #+#    #+#             */
/*   Updated: 2018/05/26 17:16:44 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "./../libft/libft.h"
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

typedef struct		s_liste
{
	char			*name_node;
	int				act;
	struct s_liste	*next;
}					t_liste;

typedef struct		s_env
{
	char			*type_term;
	char			*slg;
	char			*csr;
	char			*cln;
	char			*rst;
	char			*bgc;
	char			*txt;
	char			tch[3];
	int				csr_term;
	int				nb_arg;
	int				row;
	int				col;
	int				div;
	int				size_word_max;
	int				res;
	struct termios	tc;
	struct winsize	wsize;
	struct s_liste	*first;
	struct s_liste	*last;
}					t_env;

t_env				*g_env2;

void				ft_init_liste(t_env *env, char **argv);
void				ft_init_termcap(t_env *env);
void				ft_init_prog(t_env *env);
void				ft_reset_term(t_env *env);
void				ft_run(t_env *env);
void				ft_first(t_env *env);
void				ft_bgc_txt(t_env *env);
void				ft_press_space(t_env *env, t_liste *liste);
void				ft_bgc_txt(t_env *env);
void				ft_search_node(t_env *env, t_liste *node);
void				ft_press_delete_or_backs(t_env *env, t_liste *liste);
void				ft_size_word_max(t_env *env);
void				ft_show_column(t_env *env, char *name_node);
void				ft_init_calc_write(t_env *env);
void				ft_show(t_env *env);
void				ft_signal_tstp(int sig);
int					ft_count_liste(t_liste *first);

#endif
