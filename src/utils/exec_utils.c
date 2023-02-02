/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/02 02:03:15 by ailopez-         ###   ########.fr       */
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

_Bool	is_builtin(t_master *master, t_node *node)
{
	char	*cmd;
	_Bool	ret;
	char	*expanded_data;

	if (node->subshell)
		return (false);
	ret = false;
	if (node->subshell)
		return (false);
	ret = false;
	expanded_data = expander(ft_strdup(node->data), master);
	cmd = get_token(&expanded_data);
	if (!cmd)
		exit (0);// ERROR!!!!
	if (!ft_strncmp(cmd, "pwd", 4))
		ret = true;
		ret = true;
	if (!ft_strncmp(cmd, "cd", 3))
		ret = true;
		ret = true;
	if (!ft_strncmp(cmd, "export", 7))
		ret = true;
		ret = true;
	if (!ft_strncmp(cmd, "unset", 6))
		ret = true;
		ret = true;
	if (!ft_strncmp(cmd, "exit", 5))
		ret = true;
		ret = true;
	if (!ft_strncmp(cmd, "echo", 5))
		ret = true;
		ret = true;
	free(cmd);
	return (ret);
}

