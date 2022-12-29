/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:07:22 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/29 10:43:09 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int	executor(t_node *node)
{
	int		status;

	while (node)
	{
		node = execute_pipe (node, &status);
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

t_node	*execute_pipe(t_node *node, int *status)
{
	t_node	*node_init;

	if (!node)
		return (NULL);
	node_init = node;
	while (node)
	{
		if (node->operator == TPIP)
			pipe(node->fd);
		node->pid = fork();
		if (node->pid == 0)
			execute_child (node);
		if (node->prev && node->prev->operator == TPIP)
			close_pipe_fd (node->prev->fd);
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

void	execute_child(t_node *node)
{
	if (set_pipe(node))
		exit(EXIT_FAILURE);
	if (node->subshell)
		exit(executor(node->child));
	else
	{
		if (execve(get_path(node->tokens[0]), \
			&node->tokens[0], NULL) < 0)
		{
			perror("ba.sh: execve error");
			exit(EXIT_FAILURE);
		}
	}
}

int	set_pipe(t_node	*node)
{
	if (node->operator == TPIP)
	{
		if (dup2(node->fd[1], STDOUT_FILENO) < 0)
			return (EXIT_FAILURE);
		if (close_pipe_fd (node->fd))
			return (EXIT_FAILURE);
	}
	if (is_post_op(node, TPIP))
	{
		if (dup2(node->prev->fd[0], STDIN_FILENO) < 0)
			return (EXIT_FAILURE);
		if (close_pipe_fd (node->prev->fd))
			return (EXIT_FAILURE);
	}
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
