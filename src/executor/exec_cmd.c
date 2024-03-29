/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll <bmoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/18 12:00:38 by bmoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "signals.h"
#include "expander.h"
#include "utils.h"
#include "builtins.h"
#include "env.h"
#include <sys/stat.h>

//	---- local headers
static bool	check_permision_abs(char *path, char *original);
static int	exec(t_master *master, t_node *node);
static char	*check_cmd(t_master *master, t_node *node);
static void	check_cmd_while(t_master *master, char **cmd,
				char *original, ssize_t iter);

//	---- public
int	execute_command(t_master *master, t_node *node, int ntkn, char *token)
{
	node->tokens = malloc(sizeof(char *));
	if (node->tokens == NULL)
		exit_program(NULL, 0, 1);
	token = init_tokenizer(node->data, master, WILDCARD_ON);
	if (!token)
		return (EXIT_SUCCESS);
	node->tokens[ntkn++] = token;
	while (token)
	{
		token = get_next_token(WILDCARD_ON);
		if (token != NULL)
		{
			node->tokens = ft_realloc (node->tokens, 8 * (ntkn + 2));
			if (node->tokens == NULL)
				exit_program(NULL, 0, 1);
			node->tokens[ntkn++] = token;
		}
	}
	node->tokens[ntkn] = NULL;
	if (node->tokens)
		return (exec(master, node));
	return (EXIT_SUCCESS);
}

//	---- private
static int	exec(t_master *master, t_node *node)
{
	if (!(node->tokens[0][0]))
		exit_program(ft_strdup(": command not found"), 1, 127);
	if (!ft_strncmp(node->tokens[0], "pwd", 4))
		return (exec_pwd());
	if (!ft_strncmp(node->tokens[0], "cd", 3))
		return (exec_cd(master, node));
	if (!ft_strncmp(node->tokens[0], "export", 7))
		return (exec_export(master, node));
	if (!ft_strncmp(node->tokens[0], "unset", 6))
		return (exec_unset(master, node));
	if (!ft_strncmp(node->tokens[0], "env", 5))
		return (exec_env(master, node));
	if (!ft_strncmp(node->tokens[0], "exit", 5))
		return (exec_exit(master, node));
	if (!ft_strncmp(node->tokens[0], "echo", 5))
		return (exec_echo(node));
	init_signals(NO_INTERACTIVE);
	execve(check_cmd(master, node), node->tokens,
		env_to_array(master->env_list));
	exit_program(check_cmd(master, node), 0, 1);
	return (0);
}

static char	*check_cmd(t_master *master, t_node *node)
{
	ssize_t		iter;
	char		*cmd;
	char		*tmp;

	iter = -1;
	cmd = ft_strdup(node->tokens[0]);
	str_to_lower(cmd);
	if (cmd && ft_strchr(cmd, '/')
		&& !check_permision_abs(cmd, node->tokens[0]))
		return (cmd);
	master->path = env_get_path(master->env_list);
	if (!master->path && !check_permision_abs(cmd, node->tokens[0]))
		return (cmd);
	tmp = ft_strjoin("/\0", cmd);
	if (!tmp)
		exit_program(NULL, 0, 1);
	check_cmd_while(master, &tmp, node->tokens[0], iter);
	return (tmp);
}

//	---- private
static bool	check_permision_abs(char *path, char *original)
{
	int			error;
	struct stat	path_stat;

	error = 0;
	if (stat(path, &path_stat))
		error = print_error(ft_strdup(original), 0, 127);
	else if (S_ISDIR(path_stat.st_mode))
		exit_program(ft_strjoin(original, ": is a directory"), 1, 126);
	else if (!S_ISREG(path_stat.st_mode))
		error = print_error(ft_strjoin(original,
					": command not found"), 1, 127);
	else if (!(path_stat.st_mode & S_IXUSR))
		error = print_error(ft_strjoin(original,
					": Permission denied"), 1, 126);
	if (error)
	{
		free(path);
		exit(g_global.num_return_error);
	}
	return (error);
}

static void	check_cmd_while(t_master *master, char **cmd,
		char *original, ssize_t iter)
{
	char		*tmp;
	struct stat	path_stat;

	while (master->path[++iter])
	{
		tmp = ft_strjoin(master->path[iter], *cmd);
		if (!tmp)
			exit_program(NULL, 0, 1);
		if (!stat(tmp, &path_stat))
		{
			if (!(path_stat.st_mode & S_IXUSR))
			{
				free(tmp);
				exit_program(ft_strjoin(original, ": Permission denied"),
					1, 126);
			}
			break ;
		}
		free(tmp);
	}
	if (!master->path[iter])
		exit_program(ft_strjoin(original, ": command not found"), 1, 127);
	free(*cmd);
	*cmd = tmp;
}
