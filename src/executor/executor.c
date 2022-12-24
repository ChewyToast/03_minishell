/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:07:22 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/24 15:48:52 by aitoraudica      ###   ########.fr       */
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


int executor (t_node *node)
{
	t_node 	*node_init;
	int		status;

	node_init = node;
	while (node)
	{
		if (node->operator == TPIP)
			pipe(node->fd);
		//printf ("FD[0]->%d FD[1]->%d\n", node->fd[0], node->fd[1]);
		node->pid = fork();
		if (node->pid == 0)
		{
			logtrace("🔷 Child Born", node->data, node->fd[0], node->fd[1]);
			if (node->operator == TPIP)
			{
				//printf ("PIPE STDOUT NODE ID [%d]\n", node->node_id);
				dup2(node->fd[1], STDOUT_FILENO);
				close(node->fd[0]);
				close(node->fd[1]);
				logtrace("🟥 Closed FD", node->data, node->fd[0], node->fd[1]);
			}
			if (node->prev && node->prev->operator == TPIP)
			{
				//printf ("PIPE STDIN NODE ID [%d]\n", node->node_id);
				logtrace("🟥 Closed FD", node->data, node->prev->fd[0], node->prev->fd[1]);	
				dup2(node->prev->fd[0], STDIN_FILENO);
				close(node->prev->fd[0]);
				close(node->prev->fd[1]);
				
			}
			execve(get_path(node->tokens[0]), &node->tokens[0], NULL);
		}
		node = node->next;
	}

	//printf ("MAIN D[0]->%d FD[1]->%d\n", node_pid->fd[0], node_pid->fd[1]);


	node = node_init;
	while(node)
	{
		if (node->pid > 0)
		{
			if (node->operator == TPIP)
			{
				//printf ("Closing FD PID{%d]\n", node->pid);
				close (node->fd[1]);
				close (node->fd[0]);
			}
			waitpid(node->pid, &status, 0);
				
		}	
		node = node->next;
	}
	return (0);
}
