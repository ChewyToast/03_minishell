#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <curses.h>
#include <term.h>

int	add_history_cmd(char *command, t_history **history)
{
	t_history *new_cmd;

	if (!(*command))
		return(EXIT_SUCCESS);
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

	if (!*history)
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
	termcaps->cursor_pos = ft_strlen(buf);
}