/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/23 10:43:06 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <limits.h>

int	exec_pwd(t_node *node)
{
	char	*buff;

	ft_printf("PWD!!!\n");
	if (node->tokens[1])
		return (write(2, "ba.sh: pwd: too many arguments\n", 31));
	buff = ft_calloc(PATH_MAX + 1, 1);
	if (!getcwd(buff, PATH_MAX))
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	if (ft_printf("%s\n", buff) == -1)
	{
		free(buff);
		buff = NULL;
		return (1);// ERROR!!!!
	}
	free(buff);
	buff = NULL;
	return (0);
}

int	exec_cd(t_master *master, t_node *node)
{
	bool	err;
	char	*pwd;

	if (env_search(master->env_list, "PWD"))
		pwd = env_get_value(master->env_list, "PWD");
	else
		pwd = get_current_pwd();
	master->last_ret = 1;
	err = false;
	ft_printf("CD!!!\n");
	if (node->tokens[0] && !node->tokens[1])
	{
		if (chdir(master->tild_value) == -1)
			err = true;
	}
	else if (chdir(node->tokens[1]) == -1)
			err = true;
	if (err)
	{
		write(2, "ba.sh: ", 7);
		perror(NULL);
		exit (1);
	}
	else
	{
		if (env_change_value(master->env_list, "OLDPWD", pwd))
			error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
		if (env_change_value(master->env_list, "PWD", get_current_pwd()))
			error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	}
	master->last_ret = 0;
	return (0);
}
