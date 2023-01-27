/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 10:35:08 by aitoraudi         #+#    #+#             */
/*   Updated: 2023/01/27 19:15:02 by bmoll-pe         ###   ########.fr       */
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
	char	**cmd;
	char	*data;
	_Bool	ret;

	ret = 0;
	data = node->data;
	cmd = expander(get_token(&data), master);
	if (!cmd)
		exit (0);// ERROR!!!!
	if (!ft_strncmp(cmd[0], "pwd", 4))
		ret = 1;
	if (!ft_strncmp(cmd[0], "cd", 3))
		ret = 1;
	if (!ft_strncmp(cmd[0], "export", 3))
		ret = 1;
	if (!ft_strncmp(cmd[0], "unset", 3))
		ret = 1;
	if (!ft_strncmp(cmd[0], "exit", 3))
		ret = 1;
	free_split(cmd);
	return (ret);
}
