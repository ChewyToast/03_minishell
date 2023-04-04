/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/04 13:52:13 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"
#include "builtin_utils.h"

static bool	exec_cd_util(t_master *master, char *pwd, char *old_pwd);

int	exec_pwd(t_node *node)
{
	char	*buff;

	if (node->tokens[1])
		return (print_error(NULL, 0, 1));
	buff = ft_calloc(PATH_MAX + 1, 1);
	if (!getcwd(buff, PATH_MAX))
		return (print_error(node->tokens[1], 0, 1));
	if (ft_printf("%s\n", buff) == -1)
	{
		free(buff);
		buff = NULL;
		return (print_error(NULL, 0, 1));
	}
	free(buff);
	buff = NULL;
	return (0);
}

int	exec_cd(t_master *master, t_node *node)
{
	char	*old_pwd;
	char	*pwd;

	g_global.num_return_error = 1;
	if (env_search(master->env_list, "PWD"))
		old_pwd = env_get_value(master->env_list, "PWD");
	else
		old_pwd = get_current_pwd();
	if (!old_pwd)
		return (print_error(NULL, 0, 1));
	if (node->tokens[0] && !node->tokens[1]
		&& !env_search(master->env_list, "HOME"))
		return (print_error(ft_strdup("cd: HOME not set"), 1, 1));
	if (node->tokens[0] && !node->tokens[1])
		pwd = env_get_value(master->env_list, "HOME");
	else
		pwd = node->tokens[1];
	g_global.num_return_error = 0;
	if (exec_cd_util(master, pwd, old_pwd))
		g_global.num_return_error = 1;
	return (g_global.num_return_error);
}

static bool	exec_cd_util(t_master *master, char *pwd, char *old_pwd)
{
	bool	err;

	err = false;
	if (pwd && *pwd && chdir(pwd) == -1)
		err = true;
	if (err)
		return (print_error(ft_strjoin("cd: ", pwd), 0, 1));
	else
	{
		if (env_change_value(master->env_list, "OLDPWD", old_pwd))
			return (print_error(NULL, 0, 1));
		if (env_change_value(master->env_list, "PWD", get_current_pwd()))
			return (print_error(NULL, 0, 1));
	}
	return (0);
}
