#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <curses.h>
#include <term.h>

#define RD_BUFFER_SIZE 8192
#define CTRL_D 4
#define CTRL_C 3
#define ENTER_KEYCAP 10
#define CTRL_B 2

int		ft_putint(int c);
int		is_valid_terminal(t_termcaps *termcaps);
int		is_up_down_arrow(char *buf, t_termcaps *termcaps);
char	*extract_input(char *buf, int i);
void	write_prompt();
void	delete_single_char(t_termcaps *termcaps, char *buf, int *pos);
void	console_eof(char *buf, int pos);
void	write_hero();
void	reset_cmd_line(char *buf, int *pos, t_history **history);
void	put_history(t_history **history, t_termcaps *termcaps, char *buf, int *pos);

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

char	*msh_readline(t_termcaps *termcaps, t_history **history)
{
	char	*line;
	char	buf[RD_BUFFER_SIZE];
	int		pos;
	int		nb_char_read;

	pos = 0;
	line = NULL;
	ft_bzero(buf, RD_BUFFER_SIZE);
	write_prompt();
	while (!ft_strchr(buf, '\n'))
	{
		nb_char_read = read(STDIN_FILENO, &buf[pos], RD_BUFFER_SIZE - pos);
		//ft_printf("read %d", buf[pos]);
		if (is_up_down_arrow(&buf[pos], termcaps))
			put_history(history, termcaps, buf, &pos);
		else if (!ft_strcmp(&buf[pos], termcaps->backspace))
			delete_single_char(termcaps, buf, &pos);
		//else if (nb_char_read > 2 || (nb_char_read == 1 && is_ctrl(buf[i])))
		//	ft_bzero(&buf[i], BUFSIZ - i);
		else if (buf[pos] == CTRL_C)
			reset_cmd_line(buf, &pos, history);
		else if (buf[pos] == CTRL_D)
		 	console_eof(buf, pos);
		else if (buf[pos] == CTRL_B)
		 	write_hero();
		else
			pos += write(STDOUT_FILENO, &buf[pos], nb_char_read);
	}
	line = extract_input(buf, pos);
	add_history_cmd(line, history);
	return (line);

}

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
	//if (IS_LINUX)
	//	termcaps->backspace = tgetstr("kb", &termcaps->buffer);
	//else
		termcaps->backspace = ft_strdup("\x7f");
	termcaps->del_line = tgetstr("dl", &termcaps->buffer);
	termcaps->set_cursor_begin = tgetstr("cr", &termcaps->buffer);
	if (!termcaps->keys_on || !termcaps->keys_off
		|| !termcaps->up_arrow || !termcaps->down_arrow
		|| !termcaps->backspace || !termcaps->del_line
		|| !termcaps->set_cursor_begin)
		return (false);
	else
		return (true);
}

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

char	*extract_input(char *buf, int i)
{
	char	*input;

	buf[i - 1] = '\0';
	input = ft_strdup(buf);
	if (!input)
		exit_program("ba.sh: memery problem\n", 1);
	return (input);
}

void	delete_single_char(t_termcaps *termcaps, char *buf, int *pos)
{
	int	pos_to_del;

	pos_to_del= 2;
	if (*pos == 0 || ft_isascii(buf[*pos - 1]))
		pos_to_del = 1;
	ft_bzero(&buf[*pos - pos_to_del], RD_BUFFER_SIZE - *pos + pos_to_del);
	tputs(termcaps->del_line, 1, ft_putint);
	tputs(termcaps->set_cursor_begin, 1, ft_putint);
	write_prompt();
	*pos = write(STDOUT_FILENO, buf, ft_strlen(buf));
}

void write_prompt()
{
	ft_putstr_fd("\033[38;5;143mba.sh $ \033[0;39m", 1);
}

void	console_eof(char *buf, int pos)
{
	if (pos > 0)
	{
		buf[pos] = '\0';
		return ;
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit_program(NULL, -1);
}

int	add_history_cmd(char *command, t_history **history)
{
	t_history *new_cmd;
	t_history *temp;

	if (!(*command))
		return(EXIT_SUCCESS);
	temp = *history;
	new_cmd = malloc(sizeof(t_history));
	if (new_cmd == NULL)
		return  (EXIT_FAILURE);
	new_cmd->command = ft_strdup(command);
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	if (!*history)
		*history = new_cmd;
	else
	{
		while((*history)->next)
			*history = (*history)->next;
		new_cmd->prev = *history;
		(*history)->next = new_cmd;
		*history = new_cmd;
	}
	return(EXIT_SUCCESS);
}

void	put_history(t_history **history, t_termcaps *termcaps, char *buf, int *pos)
{
	char	*input;

	if (!history)
	{
		ft_bzero(&buf[*pos], RD_BUFFER_SIZE - *pos);
		return ;
	}
	else if (!ft_strcmp(termcaps->up_arrow, &buf[*pos]))
	{
		input = (*history)->command;
		if ((*history)->prev)
			*history = (*history)->prev;
	}
	else if (!ft_strcmp(termcaps->down_arrow, &buf[*pos]))
	{
		input = (*history)->command;
		if ((*history)->next)
			*history = (*history)->next;
	}
	tputs(termcaps->del_line, 1, ft_putint);
	tputs(termcaps->set_cursor_begin, 1, ft_putint);
	write_prompt();
	ft_bzero(buf, RD_BUFFER_SIZE);
	ft_strlcpy(buf, input, ft_strlen(input) + 1);
	*pos = write(STDOUT_FILENO, buf, ft_strlen(buf));
}

void	reset_cmd_line(char *buf, int *pos, t_history **history)
{
	ft_putstr_fd("^C\n", STDOUT_FILENO);
	num_return_error = 1;
	write_prompt();
	ft_bzero(buf, RD_BUFFER_SIZE);
	*pos = 0;
	if (*history)
	{
		while ((*history)->prev)
			*history = (*history)->prev;
	}
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
