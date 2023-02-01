#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <curses.h>
#include <term.h>

int	ft_putint(int c)
{
	return (write(1, &c, 1));
}

int	is_up_down_arrow(char *buf, t_termcaps *termcaps)
{
	if (!ft_strcmp(termcaps->up_arrow, buf))
		return(true);
	if (!ft_strcmp(termcaps->down_arrow, buf))
		return(true);
	return(false);
}

int	is_left_right_arrow(char *buf, t_termcaps *termcaps)
{
	if (!ft_strcmp(termcaps->left_arrow, buf))
		return(true);
	if (!ft_strcmp(termcaps->right_arrow, buf))
		return(true);
	return(false);
}

void	write_hero()
{

	ft_printf("%s\n\n", KBLU);
	ft_printf(" /$$      /$$ /$$$$$$ /$$   /$$ /$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$$ /$$       /$$\n");
	ft_printf("| $$$    /$$$|_  $$_/| $$$ | $$|_  $$_/ /$$__  $$| $$  | $$| $$_____/| $$      | $$\n");
	ft_printf("| $$$$  /$$$$  | $$  | $$$$| $$  | $$  | $$  \\__/| $$  | $$| $$      | $$      | $$\n");
	ft_printf("| $$ $$/$$ $$  | $$  | $$ $$ $$  | $$  |  $$$$$$ | $$$$$$$$| $$$$$   | $$      | $$\n");
	ft_printf("| $$  $$$| $$  | $$  | $$  $$$$  | $$   \\____  $$| $$__  $$| $$__/   | $$      | $$\n");
	ft_printf("| $$\\  $ | $$  | $$  | $$\\  $$$  | $$   /$$  \\ $$| $$  | $$| $$      | $$      | $$\n");
	ft_printf("| $$ \\/  | $$ /$$$$$$| $$ \\  $$ /$$$$$$|  $$$$$$/| $$  | $$| $$$$$$$$| $$$$$$$$| $$$$$$$$\n");
	ft_printf("|__/     |__/|______/|__/  \\__/|______/ \\______/ |__/  |__/|________/|________/|________/\n");
	ft_printf("\n\n");
	ft_printf("%s\t>>>>  © bmoll-pe & ailopez- <<<<<%s", U_ORANGE, DEF_COLOR);
	ft_printf("\n\n");
	write_prompt();
}

void write_prompt()
{
	ft_putstr_fd("\033[38;5;143mba.sh $ \033[0;39m", 1);
}