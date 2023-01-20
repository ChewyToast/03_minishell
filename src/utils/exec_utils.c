/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 10:35:08 by aitoraudi         #+#    #+#             */
/*   Updated: 2023/01/17 19:30:36 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <unistd.h>
#include <stdlib.h>

_Bool	close_pipe_fd(int	*fd)
{
	if (close (fd[0]))
		return (EXIT_FAILURE);
	if (close (fd[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_node	*get_next(t_node *node, int operator)
{
	while (node && node->operator != operator)
		node = node->next;
	return (node);
}

_Bool	is_post_op(t_node *node, int operator)
{
	if (node && node->prev && node->prev->operator == operator)
		return (true);
	return (false);
}

_Bool	is_in_pipe(t_node *node)
{
	if (!node)
		return (false);
	if (node->operator == TPIP)
		return (true);
	if (node->prev && node->prev->operator == TPIP)
		return (true);
	return (false);
}

_Bool	is_builtin(t_node *node)
{
	if (!ft_strncmp(node->tokens[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(node->tokens[0], "cd", 3))
		return (1);
	return (false);
}
