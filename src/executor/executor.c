/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:07:22 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/27 10:30:24 by aitoraudica      ###   ########.fr       */
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

void	close_pipe_fd (int	*fd)
{
	close (fd[0]);
	close (fd[1]);
}

// Espera a que terminen todos los procesos haste el final de un pipe
int	waiting_until_eop(t_node *node)
{
	int		status;
	
	while(node)
	{
		if (node->pid > 0)	
			waitpid(node->pid, &status, 0);
		if (node->operator != TPIP)
			break;
		node = node->next;
	}
	return(status);
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
				if (!node->prev && node->top)
				{
					dup2(node->top->prev->fd[0], STDIN_FILENO);
					close_pipe_fd (node->top->prev->fd);
				}
				if (node->operator == TPIP)
				{
					dup2(node->fd[1], STDOUT_FILENO);
					close_pipe_fd (node->fd);
				}
				if (node->prev && node->prev->operator == TPIP)
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
		if (!node->prev && node->top)
			close_pipe_fd (node->top->prev->fd);
		if (node->prev && node->prev->operator)
			close_pipe_fd (node->prev->fd);
		if (node->operator != TPIP)
			break;
		node = node->next;
	}
	*status = waiting_until_eop(node_init);
	return (node->next);
}

t_node *get_next(t_node *node, int operator)
{
	while (node && node->operator != operator)
		node = node->next;
	return (node);
}

int executor (t_node *node)
{
	int		status;
	
	while (node)
	{
		node = execute_pipe (node, &status);
		if (node && node->prev->operator == TAND)
		{
			if (status)
				node = get_next(node, TOR);
		}
		else if (node && node && node->prev->operator == TOR)
		{
			if (!status)
				node = get_next(node, TAND);
		}
	}
	return (status);
}