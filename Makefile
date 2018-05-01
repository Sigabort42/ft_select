NAME	=	ft_select

CC	=	gcc

CFLAGS	=	-Wall -Werror -Wextra

SRCS	=	ft_init.c \
		ft_run.c \
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

fclean:	clean
	@make -C libft/ fclean
	@/bin/rm -rf $(NAME)

re:	fclean all