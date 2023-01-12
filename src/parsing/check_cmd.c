/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:39:59 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/12 23:53:22 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

void	check_cmd(t_node *node)
{
	if ()





	char	*tmp;

	cmd->cmd = ft_cmd_split(*(pip->inputs->argv + 2));
	if (!cmd->cmd)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	cmd->pt_cmd = ft_substr(*(cmd->cmd), 0, ft_strlen(*(cmd->cmd)));
	if (!cmd->pt_cmd)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	if (pip->utils->path)
	{
		tmp = ft_strjoin("/\0", cmd->pt_cmd);
		if (!tmp)
			exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
		free(cmd->pt_cmd);
		cmd->pt_cmd = tmp;
		if (check_cmd_while(pip, cmd))
			return ;
		cmd->pt_cmd = ft_substr(tmp, 1, 0xffffffff);
		free(tmp);
	}
	if (access(cmd->pt_cmd, F_OK) || !ft_strrchr(cmd->pt_cmd, '/'))
		exit (clean_exit(pip, error_msg(PPX, cmd->pt_cmd, CNF, 127)));
	if (access(cmd->pt_cmd, X_OK))
		exit (clean_exit(pip, error_msg(BSH, cmd->pt_cmd, PMD, 126)));
}

static int	check_cmd_while(t_pipex *pip, t_cmds *cmd)
{
	size_t	iter;
	char	*tmp;

	iter = 0;
	while (pip->utils->path[iter])
	{
		tmp = ft_strjoin(pip->utils->path[iter], cmd->pt_cmd);
		if (!tmp)
			exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
				break ;
			free(tmp);
			exit (clean_exit(pip, error_msg(BSH, cmd->pt_cmd,
						PMD, 1)));
		}
		free(tmp);
		iter++;
	}
	if (!pip->utils->path[iter])
		return (0);
	free(cmd->pt_cmd);
	cmd->pt_cmd = tmp;
	return (1);
}