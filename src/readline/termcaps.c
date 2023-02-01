#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <curses.h>
#include <term.h>

void	init_termcaps(t_termcaps *termcaps, t_env *env_list)
{
	char	*term_type;

	if (!isatty(STDIN_FILENO))
		exit_program("ba.sh: STDIN_FILENO not pointing to terminal\n", 1);
	if (tcgetattr(STDIN_FILENO, &termcaps->old_term) == -1)
		exit_program("ba.sh: tcgetattr error\n", 1);
	term_type = env_get_value(env_list, "TERM");
	ft_printf("TERM VALUE %s\n", term_type);
	if (!term_type)
	{
		//exit_program("ba.sh: no TERM value\n", 1);
		term_type=ft_strdup("xterm-256color");
	}
	if (tgetent(termcaps->buffer, term_type) <= 0)
		exit_program("ba.sh: tgetent error\n", 1);
	if (!is_valid_terminal(termcaps))
		exit_program("ba.sh: no valid terminal\n", 1);
	free(term_type);
}

int	is_valid_terminal(t_termcaps *termcaps)
{
	termcaps->keys_on = tgetstr("ks", &termcaps->buffer);
	if (termcaps->keys_on)
		tputs(termcaps->keys_on, 1, ft_putint);
	termcaps->keys_off = tgetstr("ke", &termcaps->buffer);
	termcaps->up_arrow = tgetstr("ku", &termcaps->buffer);
	termcaps->down_arrow = tgetstr("kd", &termcaps->buffer);
	termcaps->left_arrow = tgetstr("kl", &termcaps->buffer);
	termcaps->right_arrow = tgetstr("kr", &termcaps->buffer);
	termcaps->cursor_to_left = tgetstr("le", &termcaps->buffer);
	termcaps->cursor_to_right = tgetstr("nd", &termcaps->buffer);
	termcaps->backspace = ft_strdup("\x7f");
	termcaps->del_line = tgetstr("dl", &termcaps->buffer);
	termcaps->set_cursor_begin = tgetstr("cr", &termcaps->buffer);
	if (!termcaps->keys_on || !termcaps->keys_off
		|| !termcaps->up_arrow || !termcaps->down_arrow
		|| !termcaps->backspace || !termcaps->del_line
		|| !termcaps->right_arrow || !termcaps->left_arrow
		|| !termcaps->cursor_to_right || !termcaps->cursor_to_left
		|| !termcaps->set_cursor_begin)
		return (false);
	else
		return (true);
}

void	canonical_mode_off(t_termcaps *termcaps)
{
	termcaps->new_term = termcaps->old_term;
	termcaps->new_term.c_lflag &= ~ICANON;
	termcaps->new_term.c_lflag &= ~ECHO;
	termcaps->new_term.c_lflag &= ~ISIG;
	termcaps->new_term.c_lflag &= ~IEXTEN;
	termcaps->new_term.c_iflag &= ~IXON;
	termcaps->new_term.c_cc[VMIN] = 1;
	termcaps->new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termcaps->new_term) == -1)
		exit_program("ba.sh: tcgetattr error\n", 1);
}

void	canonical_mode_on(t_termcaps *termcaps)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termcaps->old_term) == -1)
		exit_program("ba.sh: tcgetattr error\n", 1);
}