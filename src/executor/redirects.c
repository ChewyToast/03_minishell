/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:01:08 by test              #+#    #+#             */
/*   Updated: 2023/04/04 13:52:13 by test             ###   ########.fr       */
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

//	---- local headers
static bool	prepare_fd(int *fd, char *data, int8_t type);
static bool	own_here_doc(int *fd_return, t_redirect *redi, t_env *env_list);
static bool	own_here_doc_while(int *fd, char *limitator,
				t_env *env_list, bool quoted_here);
static bool	prepare_iter(t_redirect *redi, t_env *env_list,
				int *tmp_fd, int16_t *group);

//	---- public
bool	prepare_redirect(t_redirect *redi, t_env *env_list)
{
	int			tmp_fd;
	int			error;
	int16_t		*group;

	error = 0;
	tmp_fd = 0;
	group = ft_calloc(sizeof(int16_t), OPEN_MAX);
	if (!group)
		exit_program(NULL, 0, 1);
	while (redi && !error)
	{
		error = prepare_iter(redi, env_list, &tmp_fd, group);
		tmp_fd = 0;
		redi = redi->next;
	}
	while (tmp_fd++ < OPEN_MAX)
		if (group[tmp_fd] > 2)
			close(group[tmp_fd]);
	free(group);
	return (error);
}

//	---- private
static bool	prepare_iter(t_redirect *redi, t_env *env_list,
				int *tmp_fd, int16_t *group)
{
	if (redi->type == RDOC && own_here_doc(tmp_fd, redi, env_list))
		return (print_error(NULL, 0, 1));
	if (redi->type != RDOC && prepare_fd(tmp_fd, redi->data, redi->type))
		return (print_error(redi->data, 0, 1));
	if (*tmp_fd > 0)
	{
		if (dup2(*tmp_fd, redi->fd) < 0)
			return (print_error(NULL, 0, 1));
		if (group[redi->fd] > 2 && close(group[redi->fd]) < 0)
			return (print_error(NULL, 0, 1));
		group[redi->fd] = *tmp_fd;
	}
	return (0);
}

static bool	prepare_fd(int *fd, char *data, int8_t type)
{
	if (type == RIN)
		*fd = open(data, O_RDONLY);
	else if (type == ROUT)
		*fd = open(data, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (type == RADD)
		*fd = open(data, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*fd < 0)
		return (1);
	return (0);
}

static bool	own_here_doc(int *fd_return, t_redirect *redi, t_env *env_list)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0 || (!pid && own_here_doc_while(fd, redi->data,
				env_list, redi->hdoc_is_quoted)))
		return (1);
	if (close(fd[1]) < 0)
		return (1);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		*fd_return = 0;
		close(fd[1]);
		return (1);
	}
	*fd_return = fd[0];
	return (0);
}

static bool	own_here_doc_while(int *fd, char *limitator,
				t_env *env_list, bool quoted_here)
{
	char	*line;

	if (close(fd[0]) < 0)
		exit (1);
	while (42)
	{
		init_signals(HERE_DOC);
		line = readline("> ");
		init_signals(NO_INTERACTIVE);
		if (g_global.is_ctrlc || !line)
			exit (1);
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
