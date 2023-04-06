/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 14:20:16 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"
#include "builtin_utils.h"

static bool	exec_cd_util(t_master *master, char *pwd, char *old_pwd);

int	exec_pwd(void)
{
	char	*buff;

	buff = ft_calloc(PATH_MAX + 1, 1);
	if (!getcwd(buff, PATH_MAX))
		return (print_error(NULL, 0, 1));
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
	if (node->tokens[0] && !node->tokens[1])
		free(pwd);
	free(old_pwd);
	return (g_global.num_return_error);
}

static bool	exec_cd_util(t_master *master, char *pwd, char *old_pwd)
{
	char	*tmp;

	tmp = NULL;
	if (pwd && *pwd && chdir(pwd) == -1)
		return (print_error(ft_strjoin("cd: ", pwd), 0, 1));
	if (env_search(master->env_list, "OLDPWD"))
	{
		if (env_change_value(master->env_list, "OLDPWD", old_pwd))
			return (print_error(NULL, 0, 1));
	}
	else
		env_set_value(&master->env_list, "OLDPWD", old_pwd);
	tmp = get_current_pwd();
	if (!tmp)
		return (print_error(NULL, 0, 1));
	if (env_change_value(master->env_list, "PWD", tmp))
		return (print_error(NULL, 0, 1));
	free(tmp);
	return (0);
}
