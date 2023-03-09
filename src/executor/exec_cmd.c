/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/03/09 19:40:01 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "expander.h"
#include "utils.h"
#include "builtins.h"
#include "env.h"

//	---- local headers
static bool	check_permision(char *cmd);
static int	exec(t_master *master, t_node *node);
static char	*check_cmd(t_master *master, t_node *node);
static void	check_cmd_while(t_master *master, char **cmd, char *original);

//	---- public
void	execute_command(t_master *master, t_node *node)
{
	int		num_tokens;
	char	*token;

	num_tokens = 0;
	node->tokens = malloc(sizeof(char *));
	if (node->tokens == NULL)
		exit_program(NULL, 0, 1);
	token = init_tokenizer(node->data, master, WILDCARD_ON);
	str_to_lower(token);
	node->tokens[num_tokens++] = token;
	while (token)
	{
		token = get_next_token(WILDCARD_ON);
		if (token != NULL)
		{
			node->tokens = ft_realloc (node->tokens, sizeof(char *) * (num_tokens + 2));
			if (node->tokens == NULL)
				exit_program(NULL, 0, 1);
			node->tokens[num_tokens++] = token;
		}
	}
	node->tokens[num_tokens] = NULL;
	exec(master, node);
}

//	---- private
static int	exec(t_master *master, t_node *node)
{
	if (node->tokens[0][0] == '\0')//esto puede dar seg fault?@to_do
		return (EXIT_SUCCESS);
	if (!ft_strncmp(node->tokens[0], "pwd", 4))//lo digo porque si mandas null a strncmp da segfault
		return (exec_pwd(node));
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
	execve(check_cmd(master, node), node->tokens, env_to_array(master->env_list));
	exit_program(NULL, 0, 1);
	return (1);
}

static char	*check_cmd(t_master *master, t_node *node)
{
	char	*cmd;
	char	*tmp;

	cmd = node->tokens[0];
	if (cmd && (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] && cmd[1] == '/')) && !check_permision(cmd))
		return (cmd);
	master->path = env_get_path(master->env_list);
	if (!master->path)
		exit_program(NULL, 0, 1);
	tmp = ft_strjoin("/\0", cmd);
	if (!tmp)
		exit_program(NULL, 0, 1);
	check_cmd_while(master, &tmp, cmd);
	return (tmp);
}

static bool	check_permision(char *cmd)
{
	if (access(cmd, F_OK))
		exit_program(ft_strjoin(cmd, ": command not found"), 1, 127);
	if (access(cmd, X_OK))
		exit_program(cmd, 0, 126);
	return (0);
}

//	---- private
static void	check_cmd_while(t_master *master, char **cmd, char *original)
{
	size_t	iter;
	char	*tmp;

	iter = 0;
	while (master->path[iter])
	{
		tmp = ft_strjoin(master->path[iter], *cmd);
		if (!tmp)
			exit_program(NULL, 0, 1);
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
				break ;
			free(tmp);
			exit_program(NULL, 0, 1);
		}
		free(tmp);
		iter++;
	}
	if (!master->path[iter])
		exit_program(ft_strjoin(original, ": command not found"), 1, 127);
	free(*cmd);
	*cmd = tmp;
}
