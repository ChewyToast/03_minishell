/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 17:02:25 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"
#include "builtin_utils.h"

static bool	exec_cd_util(t_master *master,
				t_node *node, char *pwd, char *old_pwd);
static bool	get_cd_dir(t_master *master, t_node *node, char **pwd);
int			ft_strcmp(const char *s1, const char *s2);

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

	pwd = NULL;
	old_pwd = NULL;
	g_global.num_return_error = 1;
	if (env_search(master->env_list, "PWD"))
	{
		old_pwd = env_get_value(master->env_list, "PWD");
		if (!old_pwd)
			return (print_error(NULL, 0, 1));
	}
	if (get_cd_dir(master, node, &pwd))
		return (1);
	g_global.num_return_error = 0;
	if (exec_cd_util(master, node, pwd, old_pwd))
		g_global.num_return_error = 1;
	if (node->tokens[0] && !node->tokens[1])
		free(pwd);
	if (old_pwd)
		free(old_pwd);
	return (g_global.num_return_error);
}

static bool	get_cd_dir(t_master *master, t_node *node, char **pwd)
{
	if (node->tokens[0] && !node->tokens[1]
		&& !env_search(master->env_list, "HOME"))
		return (print_error(ft_strdup("cd: HOME not set"), 1, 1));
	if (node->tokens[0] && !node->tokens[1])
		*pwd = env_get_value(master->env_list, "HOME");
	else if (node->tokens[0] && node->tokens[1]
		&& !ft_strcmp(node->tokens[1], "-"))
	{
		if (!env_search(master->env_list, "OLDPWD"))
			return (print_error(ft_strdup("cd: OLDPWD not set"), 1, 1));
		*pwd = env_get_value(master->env_list, "OLDPWD");
	}
	else if (node->tokens[1])
		*pwd = node->tokens[1];
	if (!(*pwd))
		exit_program(NULL, 0, 1);
	return (0);
}

static bool	exec_cd_util(t_master *master, t_node *node,
				char *pwd, char *old_pwd)
{
	char	*tmp;

	tmp = NULL;
	if (pwd && *pwd && chdir(pwd) == -1)
		return (print_error(ft_strjoin("cd: ", pwd), 0, 1));
	if (old_pwd && env_search(master->env_list, "OLDPWD"))
	{
		if (env_change_value(master->env_list, "OLDPWD", old_pwd))
			return (print_error(NULL, 0, 1));
	}
	else if (old_pwd)
		env_set_value(&master->env_list, "OLDPWD", old_pwd);
	else if (!old_pwd)
		env_unset_node(master, "OLDPWD");
	tmp = get_current_pwd();
	if (!tmp)
		return (print_error(NULL, 0, 1));
	if (env_change_value(master->env_list, "PWD", tmp))
		return (print_error(NULL, 0, 1));
	free(tmp);
	if (node->tokens[0] && pwd && node->tokens[1]
		&& !ft_strcmp(node->tokens[1], "-"))
		if (write(1, pwd, ft_strlen(pwd)) < 0 || write(1, "\n", 1) < 0)
			return (print_error(NULL, 0, 1));
	return (0);
}
