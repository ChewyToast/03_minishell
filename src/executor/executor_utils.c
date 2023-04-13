/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:22:09 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/13 18:41:12 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "expander.h"
#include "utils.h"

int	status_return(int status);

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
	g_global.is_ctrlc = 0;
	return (status_return(status));
}

int	status_return(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			exit_program(NULL, 0, 1);
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			return (130);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
			return (131);
		}
	}
	return (1);
}
