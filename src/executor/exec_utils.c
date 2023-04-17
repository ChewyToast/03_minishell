/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:09:14 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/03 19:09:26 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "expander.h"
#include "utils.h"

bool	close_pipe_fd(int	*fd)
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
	if (node)
		node = node->next;
	return (node);
}

bool	is_post_op(t_node *node, int operator)
{
	if (node && node->prev && node->prev->operator == operator)
		return (true);
	return (false);
}

bool	is_in_pipe(t_node *node)
{
	if (!node)
		return (false);
	if (node->operator == TPIP)
		return (true);
	if (node->prev && node->prev->operator == TPIP)
		return (true);
	return (false);
}

bool	is_builtin(t_master *master, t_node *node)
{
	char	*cmd;
	bool	ret;

	if (node->subshell)
		return (false);
	ret = false;
	cmd = init_tokenizer(node->data, master, WILDCARD_ON);
	if (cmd && !ft_strncmp(cmd, "pwd", 4))
		ret = true;
	if (cmd && !ft_strncmp(cmd, "cd", 3))
		ret = true;
	if (cmd && !ft_strncmp(cmd, "export", 7))
		ret = true;
	if (cmd && !ft_strncmp(cmd, "unset", 6))
		ret = true;
	if (cmd && !ft_strncmp(cmd, "exit", 5))
		ret = true;
	if (cmd && !ft_strncmp(cmd, "echo", 5))
		ret = true;
	if (cmd && !ft_strncmp(cmd, "env", 5))
		ret = true;
	if (cmd)
		free(cmd);
	return (ret);
}
