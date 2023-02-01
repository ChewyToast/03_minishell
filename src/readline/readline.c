#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <curses.h>
#include <term.h>

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
	termcaps->cursor_pos = 0;
	while (!ft_strchr(buf, '\n'))
	{
		nb_char_read = read(STDIN_FILENO, &buf[pos], RD_BUFFER_SIZE - pos);
		//ft_printf("read %d", buf[pos]);
		if (is_up_down_arrow(&buf[pos], termcaps))
			put_history(history, termcaps, buf, &pos);
		else if (is_left_right_arrow(&buf[pos], termcaps))
			move_cursor(termcaps, buf, &pos);
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
		{
			termcaps->cursor_pos += nb_char_read;
			pos += write(STDOUT_FILENO, &buf[pos], nb_char_read);
		}
		//printf("\nbuffer [%s] - cursor [%d]\n", buf, termcaps->cursor_pos);
	}
	line = extract_input(buf, pos);
	add_history_cmd(line, history);
	return (line);

}

void	move_cursor(t_termcaps *termcaps, char *buf, int *pos)
{
	if (!ft_strcmp(termcaps->left_arrow, &buf[*pos]) && termcaps->cursor_pos != 0)
	{
		termcaps->cursor_pos--;
		tputs(termcaps->cursor_to_left, 1, ft_putint);
	}
	else if (!ft_strcmp(termcaps->right_arrow, &buf[*pos]) && termcaps->cursor_pos < *pos)
	{
		termcaps->cursor_pos++;
		tputs(termcaps->cursor_to_right, 1, ft_putint);
	}
	buf[*pos] = 0;
	return;
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
	//int	pos_to_del;

	// pos_to_del= 2;
	// if (*pos == 0 || ft_isascii(buf[*pos - 1]))
	// 	pos_to_del = 1;
	termcaps->cursor_pos--;
	ft_bzero(&buf[*pos - 1], RD_BUFFER_SIZE - *pos + 1);
	tputs(termcaps->del_line, 1, ft_putint);
	tputs(termcaps->set_cursor_begin, 1, ft_putint);
	write_prompt();
	*pos = write(STDOUT_FILENO, buf, ft_strlen(buf));
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