/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:07:22 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/24 19:05:35 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <unistd.h>

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
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
	return (NULL);
}

void close_pipes_pre(t_node * node)
{
	while (node)
	{
		if (node && node->operator == TPIP)
		{
			close (node->fd[0]);
			close (node->fd[1]);
		}
		node = node->prev;
	}
}

int executor (t_node *node)
{
	t_node 	*node_init;
	int		status;

	node_init = node;
	while (node)
	{
		if (node->operator == TPIP)
			pipe(node->fd);
		node->pid = fork();
		if (node->pid == 0)
		{
			logtrace("🔷 Child Born", node->data, node->fd[0], node->fd[1]);
			if (node->operator == TPIP)
			{
				dup2(node->fd[1], STDOUT_FILENO);
				logtrace("🔰 NODE STDOUT", node->data, node->fd[1], 255);					
				logtrace("🟥 Closed FD", node->data, node->fd[0], node->fd[1]);
				close(node->fd[0]);
				close(node->fd[1]);
			}
			if (node->prev && node->prev->operator == TPIP)
			{
				dup2(node->prev->fd[0], STDIN_FILENO);
				logtrace("🔰 NODE STDIN", node->data, node->prev->fd[0], 255);	
				logtrace("🟥 Closed FD", node->data, node->prev->fd[0], node->prev->fd[1]);	
				close_pipes_pre(node->prev);
			}
			
			logtrace("⛔ Execute", node->data, 0, 0);	
			execve(get_path(node->tokens[0]), &node->tokens[0], NULL);
		}
		node = node->next;
	}

	node = node_init;
	while (node)
	{
		if (node->operator == TPIP)
		{
			close (node->fd[1]);
			close (node->fd[0]);
		}
		node=node->next;
	}
	node = node_init;
	while(node)
	{
		if (node->pid > 0)	
			waitpid(node->pid, &status, 0);
		node = node->next;
	}
	printf ("\nReturn Value [%d]\n", WEXITSTATUS(status));
	return (0);
}
