/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:01:08 by test              #+#    #+#             */
/*   Updated: 2023/03/09 21:15:23 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "readline.h"
#include "signals.h"
#include <fcntl.h>
#include "redirects.h"
#include "executor.h"

//	---- local headers
static bool	prepare_fd(int *fd, char *data, int8_t type);
static bool	own_here_doc(int *fd_return, t_redirect *redi, t_env *env_list);
static bool	own_here_doc_while(int *fd, char *limitator, t_env *env_list, bool quoted_here);

//	---- public
bool	prepare_redirect(t_fdmanage **fdman, t_redirect *redi, t_env *env_list)
{
	int			tmp_fd;

	tmp_fd = 0;
	while (redi)
	{
		if (redi->type == RDOC && own_here_doc(&tmp_fd, redi, env_list))
			print_error(NULL, 0, 1);
		if (redi->type != RDOC && prepare_fd(&tmp_fd, redi->data, redi->type))
			print_error(redi->data, 0, 1);
		if (tmp_fd > 0)
		{
			if (dup2(tmp_fd, redi->fd) < 0)
				print_error(NULL, 0, 1);
			if ((close_fdman(fdman, redi->fd)) || (add_fdman(fdman, redi->fd, tmp_fd)))// no estoy seguro de si esto esta bien @to_do
				print_error(NULL, 0, 1);
		}
		redi = redi->next;
	}
	return (0);
}

bool	add_fdman(t_fdmanage **fdman, int index, int fd)
{
	t_fdmanage 	*toadd;

	toadd = malloc(sizeof(t_fdmanage));
	if (!toadd)
		return (1);
	toadd->index = index;
	toadd->fd = fd;
	toadd->next = *fdman;
	*fdman = toadd;
	return (0);
}

bool	close_fdman(t_fdmanage **fdman, int index)
{
	t_fdmanage 	*tmp;
	t_fdmanage 	*last;

	tmp = *fdman;
	last = NULL;
	while (tmp)
	{
		if (tmp->index == index)
		{
			if (tmp->fd > 1 && close(tmp->fd))
				return (1);
			if (!last)
				{*fdman = tmp->next;tmp = tmp->next;}
			else
				{last->next = tmp->next;tmp = last->next;}
			free(tmp);
			return (0);
		}
		else
			{last = tmp;tmp = tmp->next;}
	}
	return (0);
}

//	---- private
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
	if (pid < 0 || (!pid && own_here_doc_while(fd, redi->data, env_list, redi->hdoc_is_quoted)))
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

static bool	own_here_doc_while(int *fd, char *limitator, t_env *env_list, bool quoted_here)
{
	char	*line;

	if (close(fd[0]) < 0)
		exit (1);
	while (42)
	{
		init_signals(HERE_DOC);
		line = readline("> ");
		init_signals(NO_INTERACTIVE);
		if (global.is_ctrlC || !line)
			exit (1);
		line = str_dollar_expander(line, quoted_here, env_list);
		if (!ft_strncmp(line, limitator, 0xffffffff))
			break ;
		if (write(fd[1], line, ft_strlen(line)) < 0 || write(fd[1], "\n", 1) < 0)
		{
			free(line);
			close(fd[1]);
			exit (1);
		}
		free(line);
	}
	if (line)
		free(line);
	if (close(fd[1]) < 0)
		exit (1);
	exit (0);
}
