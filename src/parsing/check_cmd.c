/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:39:59 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/15 17:17:11 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

static int	check_cmd_while(t_master *master, char *cmd);

char	*check_cmd(t_master *master, t_node *node)
{
	char	*cmd;

	cmd = node->tokens[0];
	write(1, "*", 1);
	if (master->path)
	{
		cmd = ft_strjoin("/\0", node->tokens[0]);
		if (!cmd)
			error("ba.sh: memory alloc error\n", 1);
		if (check_cmd_while(master, cmd))
			return (cmd);
	}
	ft_printf("cmd: %s master->path: %p\n", cmd, master->path);
	if (access(cmd, F_OK) || !ft_strrchr(cmd, '/'))
		error("ba.sh: Command not found\n", 1);
		// exit (clean_exit(pip, error_msg(PPX, cmd, CNF, 127)));
	if (access(cmd, X_OK))
		error("ba.sh: permission deneied\n", 1);
		// exit (clean_exit(pip, error_msg(BSH, cmd, PMD, 126)));
	return (cmd);
}

static int	check_cmd_while(t_master *master, char *cmd)
{
	size_t	iter;
	char	*tmp;

	iter = 0;
	while (master->path[iter])
	{
		tmp = ft_strjoin(master->path[iter], cmd);
		if (!tmp)
			error("ba.sh: memory alloc error", 1);
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
				break ;
			free(tmp);
			error("ba.sh: permission denied\n", 1);
		}
		free(tmp);
		iter++;
	}
	if (!master->path[iter])
		return (0);
	free(cmd);
	cmd = tmp;
	return (1);
}