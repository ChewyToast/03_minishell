/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:34:32 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/13 18:39:36 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "readline.h"
#include "signals.h"
#include <fcntl.h>
#include "redirects.h"
#include "executor.h"
#include "defines.h"
#include "env.h"

bool	is_last_here(t_redirect *redi, int *tmp_fd)
{
	int8_t		fd;
	t_redirect	*tmp;

	if (!redi || *tmp_fd < 3)
		return (0);
	tmp = redi->next;
	fd = redi->fd;
	while (tmp)
	{
		if (tmp->type == RDOC && tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	close(*tmp_fd);
	return (0);
}

bool	own_here_doc(int *fd_return, t_redirect *redi, t_env *env_list)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid)
		own_here_doc_while(fd, redi->data, env_list, redi->hdoc_is_quoted);
	if (close(fd[1]) < 0)
		return (1);
	waitpid(pid, &status, 0);
	*fd_return = fd[0];
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) != 1)
			return (0);
	*fd_return = 0;
	close(fd[1]);
	return (1);
}

void	own_here_doc_while(int *fd, char *limitator, t_env *env_list,
			bool quoted_here)
{
	char	*line;

	if (close(fd[0]) < 0)
		exit (1);
	while (42)
	{
		init_signals(HERE_DOC);
		do_sigign(SIGQUIT);
		line = readline("> ");
		if (g_global.is_ctrlc || !line)
			exit (0);
		line = str_dollar_expander(line, quoted_here, env_list);
		if (!ft_strncmp(line, limitator, 0xffffffff))
			break ;
		if (write(fd[1], line, ft_strlen(line)) < 0 || write(fd[1], "\n", 1) < 0)
			exit_program(NULL, 0, 1);
		free(line);
	}
	if (line)
		free(line);
	if (close(fd[1]) < 0)
		exit (1);
	exit (0);
}
