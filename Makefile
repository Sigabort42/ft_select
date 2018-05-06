#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/06 09:50:26 by elbenkri          #+#    #+#              #
#    Updated: 2018/05/06 12:25:03 by elbenkri         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	ft_select

CC	=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g3 -fsanitize=address

SRCS	=	ft_init.c \
		ft_run.c \
		ft_utils.c \
		ft_liste.c \
		ft_show_column.c \
		main.c \

OBJS	=	$(SRCS:.c=.o)

LIBFT	=	libft/libft.a

LIBTERM	=	-ltermcap

all:		$(NAME)

$(NAME):	$(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBTERM) -o $(NAME)

clean:
	@make -C libft/ clean
	@/bin/rm -rf $(OBJS)

fclean:		clean
	@make -C libft/ fclean
	@/bin/rm -rf $(NAME)

re:		fclean all