/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:01:08 by test              #+#    #+#             */
/*   Updated: 2023/03/02 14:32:13 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "readline.h"
#include <fcntl.h>

//	---- local headers
static int	prepare_fd(int *fd, char *data, int8_t type);
static bool	own_here_doc(int *fd_return, t_redirect *redi);
static bool	own_here_doc_while(int *fd, char *limitator);

//	---- public
_Bool	prepare_redirect(int *fd, int8_t mode, t_redirect *redi)
{
	int	fd2;

	fd2 = 0;
	if (!redi)
		return (0);
	while (redi)
	{
		if (redi->type == mode || redi->type == mode + 2)
			if (fd2 > 0)// Hemos encontrado otro, por lo que cerramos el anterior
				close(fd2);	
		if (redi->type == mode)
		{
			if (prepare_fd(&fd2, redi->data, redi->type) < 0)
				return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		}
		else if (redi->type == mode + 2)
		{
			if (redi->type == RADD)
			{
				if (prepare_fd(&fd2, redi->data, redi->type) < 0)
					return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
			}
			else if (own_here_doc(&fd2, redi))
				return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		}
		redi = redi->next;
	}
	*fd = fd2;
	return (0);
}

//	---- private
static int	prepare_fd(int *fd, char *data, int8_t type)
{
	if (type == RIN)
	{
		if (access(data, F_OK))
			return (print_error(ft_strjoin("ba.sh: ", ft_strjoin(data, ": No such a file or directory\n")), 0));
		if (access(data, R_OK))
			return (print_error(ft_strjoin("ba.sh: ", ft_strjoin(data, ": Permision denied\n")), 0));
		*fd = open(data, O_RDONLY);
	}
	else if (type == ROUT)
	{
		if (!access(data, F_OK))
			if (access(data, W_OK))
				return (print_error(ft_strjoin("ba.sh: ", ft_strjoin(data, ": Permision denied\n")), 0));
		*fd = open(data, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	else if (type == RADD)
	{
		if (!access(data, F_OK))
			if (access(data, W_OK))
				return (print_error(ft_strjoin("ba.sh: ", ft_strjoin(data, ": Permision denied\n")), 0));
		*fd = open(data, O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
	return (*fd);
}

static bool	own_here_doc(int *fd_return, t_redirect *redi)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid && own_here_doc_while(fd, redi->data))
		return (1);
	if (close(fd[1]) < 0)
		return (1);//ERROR!
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		close(fd[1]);
		return (1);//TENGO MIEDO YA VAN DEMASIADOS ERRORES
	}
	*fd_return = fd[0];
	return (0);
}


static bool	own_here_doc_while(int *fd, char *limitator)
{
	char	*line;

	if (close(fd[0]) < 0)
		return (1);//ERROR!
	while (42)
	{
		line = readline("> ");
		if (!line)
			exit_program(NULL, 0);// nose que haceer tengo miedo
		if (!ft_strncmp(line, limitator, 0xffffffff))
			break ;
		if (write(fd[1], line, ft_strlen(line)) < 0 || write(fd[1], "\n", 1) < 0)
		{
			free(line);
			if (close(fd[1]) < 0)
				exit (1);//ERROR!
			return (1);//ERROR!
		}
		free(line);
	}
	if (close(fd[1]) < 0)
		exit (1);//ERROR!
	if (line)
		free(line);
	exit (0);
}