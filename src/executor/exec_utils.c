/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/29 17:44:51 by ailopez-         ###   ########.fr       */
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
	str_to_lower(cmd);
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
