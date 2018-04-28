#include "libft/libft.h"
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	ft_background_txt(char *bg, char *txt)
{
	tputs(tparm(bg, COLOR_WHITE), 1, ft_putchar);
	tputs(tparm(txt, COLOR_BLACK), 1, ft_putchar);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	char	*type_term = getenv("TERM");
	char	*souligne;
	char	*bg;
	char	*txt;
	char	*reset;
	char	*cursor;
	char	*clean;
	char	buf[3];
	struct termios lol;
	int	i;
	int	x;
	int	ret;
	char	*tab_iter;

	i = 1;
	x = 1;
	tab_iter = ft_strnew(argc);
	if (tgetent(0, type_term) == ERR)
		perror("tgetent");
	bg = tgetstr("AB", NULL);
	txt = tgetstr("AF", NULL);
	souligne = tgetstr("us", NULL);
	reset = tgetstr("me", NULL);
	cursor = tgetstr("cm", NULL);
	clean = tgetstr("cl", NULL);
	tputs(clean, 1, ft_putchar);
	tputs(tgoto(cursor, 0, 0), 1, ft_putchar);
	while (argv[i])
	{
		if (i == x)
			ft_background_txt(bg, txt);
		else
			tputs(reset, 1, ft_putchar);
		printf("%s\n", argv[i++]);
	}
	tcgetattr(0, &lol);
	lol.c_lflag = ~(ICANON|ECHO);
	lol.c_cc[VMIN] = 1;
	lol.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &lol);
	tab_iter = memset(tab_iter, '0', argc);
	while ((ret = read(0, buf, 3)) > 0)
	{
		i = 1;
		tputs(clean, 1, ft_putchar);
		tputs(tgoto(cursor, 0, 0), 1, ft_putchar);
		buf[ret + 1] = 0;
		if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
			x++;
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
			x--;
		if (x == argc)
			x = 1;
		else if (x == 0)
			x = argc - 1;
		while (argv[i])
		{
			if (i == x)
			{
				ft_background_txt(bg, txt);
				if (buf[0] == 32)
				{
					if (tab_iter[i] == '0')
						tab_iter[i] = '1';
					else
						tab_iter[i] = '0';
				}
			}
			else
				tputs(reset, 1, ft_putchar);
			if (tab_iter[i] == '1')
				tputs(souligne, 1, ft_putchar);
			printf("%s\n", argv[i++]);
		}
		tputs(reset, 1, ft_putchar);
		printf("\nbuf = %d %d %d\n", buf[0], buf[1], buf[2]);
		bzero(buf, 3);
	}
	return (0);
}
