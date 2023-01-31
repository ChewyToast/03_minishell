/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/01/31 10:35:31 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

t_node	*execute_pipe(t_master *master, t_node *node, int *status);
int		set_pipe(t_node	*node);
int		waiting_pipe(t_node *node);
void	execute_child(t_master *master, t_node *node);

int	executor(t_master *master, t_node *node)
{
	int		status;

	while (node)
	{
		node = execute_pipe(master, node, &status);
		if (is_post_op(node, TAND))
		{
			if (status)
				node = get_next(node, TOR);
		}
		else if (is_post_op(node, TOR))
		{
			if (!status)
				node = get_next(node, TAND);
		}
	}
	return (status);
}

t_node	*execute_pipe(t_master *master, t_node *node, int *status)
{
	t_node	*node_init;

	if (!node)
		return (NULL);
	if (!is_in_pipe(node) && is_builtin(master, node))
	{
		*status = execute_command(master, node);
		return (node->next);
	}
	node_init = node;
	while (node)
	{
		if (node->operator == TPIP)
			pipe(node->fd);
		node->pid = fork();
		if (node->pid < 0)
			exit (EXIT_FAILURE);// ERROR!!!!!!!!
		if (node->pid == 0)
			execute_child(master, node);
		if (node->prev && node->prev->operator == TPIP)
			close_pipe_fd(node->prev->fd);
		if (node->operator != TPIP)
			break ;
		node = node->next;
	}
	*status = waiting_pipe(node_init);
	if (node)
		return (node->next);
	else
		return (NULL);
}

void	execute_child(t_master *master, t_node *node)
{
	if (set_pipe(node))
		exit(EXIT_FAILURE);
	if (node->subshell)
		exit(executor(master, node->child));
	else
		exit (execute_command(master, node));
}

int	set_pipe(t_node	*node)
{
	int	fd_out;
	int	fd_in;

	fd_out = STDOUT_FILENO;
	fd_in = STDIN_FILENO;
	if (node->operator == TPIP)
		fd_out = node->fd[STDOUT_FILENO];
	if (is_post_op(node, TPIP))
		fd_in = node->prev->fd[STDIN_FILENO];

	// REDIRECTS FD FUNCTION

	if (dup2(fd_out, STDOUT_FILENO) < 0)
		return (EXIT_FAILURE);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		return (EXIT_FAILURE);
	if (node->operator == TPIP && close_pipe_fd (node->fd))
		return (EXIT_FAILURE);
	if (is_post_op(node, TPIP) && close_pipe_fd (node->prev->fd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	waiting_pipe(t_node *node)
{
	int	status;

	while (node)
	{
		if (node->pid > 0)
			waitpid(node->pid, &status, 0);
		if (WIFEXITED(status))
			node->status = WEXITSTATUS(status);
		if (node->operator != TPIP)
			break ;
		node = node->next;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}