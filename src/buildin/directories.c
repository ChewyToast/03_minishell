/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/02/21 17:11:39 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <limits.h>
#include <errno.h>

int	exec_pwd(t_node *node)
{
	char	*buff;

	if (node->tokens[1])
		return (print_error(ft_strdup("ba.sh: pwd: too many arguments"), 31));
	buff = ft_calloc(PATH_MAX + 1, 1);
	if (!getcwd(buff, PATH_MAX))
		return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
	if (ft_printf("%s\n", buff) == -1)
	{
		free(buff);
		buff = NULL;
		return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
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
	num_return_error = 1;
	err = false;
	if (node->tokens[0] && !node->tokens[1])
	{
		if (chdir(master->tild_value) == -1)
			err = true;
	}
	else if (chdir(node->tokens[1]) == -1)
			err = true;
	if (err)
		return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
	else
	{
		if (env_change_value(master->env_list, "OLDPWD", pwd))
			return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
		if (env_change_value(master->env_list, "PWD", get_current_pwd()))
			return (print_error(ft_strdup("ba.sh: Error trying to allocate memory"), 1));
	}
	num_return_error = 0;
	return (0);
}
