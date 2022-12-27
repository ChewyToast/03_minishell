/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:07:22 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/27 21:17:08 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <unistd.h>

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <signal.h>
#include <unistd.h>

int		is_post_op (t_node *node, int operator);
int		is_piped_child (t_node *node);
t_node	*get_next(t_node *node, int operator);
void	close_pipe_fd (int	*fd);
char	*get_path (char	*cmd);
int		waiting_pipe(t_node *node);
t_node	*execute_pipe (t_node *node, int *status);

int executor (t_node *node)
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

// Ejecuta el pipe hasta el final, es decir hasta que se encuentre un nodo que no tiene pipe
t_node *execute_pipe (t_node *node, int *status)
{
	t_node 	*node_init;
	
	if (!node)
		return (NULL);
	node_init = node;
	while (node)
	{
		if (node->operator == TPIP)
			pipe(node->fd);
		node->pid = fork();
		if (node->pid == 0)
		{		
			if (node->subshell)
				exit(executor(node->child));
			else
			{
				if (!node->prev && is_piped_child(node))
				{
					dup2(node->top->prev->fd[0], STDIN_FILENO);
					close_pipe_fd (node->top->prev->fd);
				}
				if (node->operator == TPIP)
				{
					dup2(node->fd[1], STDOUT_FILENO);
					close_pipe_fd (node->fd);
				}
				if (is_post_op(node, TPIP))
				{
					dup2(node->prev->fd[0], STDIN_FILENO);
					close_pipe_fd (node->prev->fd);
				}
				if (execve(get_path(node->tokens[0]), &node->tokens[0], NULL) < 0)
				{
					perror("ba.sh: execve error");
					exit(1);
				}
			}
		}
		if (!node->prev && is_piped_child(node))
			close_pipe_fd (node->top->prev->fd);
		if (node->prev && node->prev->operator == TPIP)
			close_pipe_fd (node->prev->fd);
		if (node->operator != TPIP)
			break;
		node = node->next;
	}
	*status = waiting_pipe(node_init);
	if (node)
		return (node->next);
	else
		return (NULL);
}

// Espera a que terminen todos los procesos haste el final de un pipe
int	waiting_pipe(t_node *node)
{
	int		status;
	
	while(node)
	{
		if (node->pid > 0)	
			waitpid(node->pid, &status, 0);
		if (WIFEXITED(status))
			node->status = WEXITSTATUS(status);
		if (node->operator != TPIP)
			break;
		node = node->next;
	}
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	else
		return (-1);
}

void	close_pipe_fd (int	*fd)
{
	close (fd[0]);
	close (fd[1]);
}

t_node *get_next(t_node *node, int operator)
{
	while (node && node->operator != operator)
		node = node->next;
	return (node);
}

int is_piped_child (t_node *node)
{
	if (node->top && node->top->prev && node->top->prev->operator == TPIP)
		return (1);
	return (0);
}

int is_post_op (t_node *node, int operator)
{
	if (node && node->prev && node->prev->operator == operator)
		return (1);
	return (0);
}

char	*get_path (char	*cmd)
{
	if (!ft_strncmp(cmd, "sleep", 7))
		return(ft_strjoin("/bin/", cmd));	
	if (!ft_strncmp(cmd, "ls", 3))
		return(ft_strjoin("/bin/", cmd));
	if (!ft_strncmp(cmd, "echo", 7))
		return(ft_strjoin("/bin/", cmd));		
	if (!ft_strncmp(cmd, "cat", 5))
		return(ft_strjoin("/bin/", cmd));		
	if (!ft_strncmp(cmd, "grep", 3))
		return(ft_strjoin("/usr/bin/", cmd));
	return (cmd);
}