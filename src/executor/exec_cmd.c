/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/03/01 17:18:23 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "expander.h"
#include "utils.h"
#include "builtins.h"
#include "env.h"

//	---- local headers
static int	exec(t_master *master, t_node *node);
static char	*check_cmd(t_master *master, t_node *node);
static int	check_cmd_while(t_master *master, char **cmd);

//	---- public
int	execute_command(t_master *master, t_node *node)
{
	int		num_tokens;
	char	*token;

	num_tokens = 0;
	node->tokens = malloc(sizeof(char *));
	if (node->tokens == NULL)
		return (EXIT_FAILURE);
	token = init_tokenizer(node->data, master);
	str_to_lower(token);
	node->tokens[num_tokens++] = token;
	while (token)
	{
		token = get_next_token();
		if (token != NULL)
		{
			node->tokens = ft_realloc (node->tokens, sizeof(char *) * (num_tokens + 2));
			if (node->tokens == NULL)
				return (EXIT_FAILURE);
			node->tokens[num_tokens++] = token;
		}
	}
	node->tokens[num_tokens] = NULL;
	return (exec(master, node));
}

//	---- private
static int	exec(t_master *master, t_node *node)
{
	if (!ft_strncmp(node->tokens[0], "pwd", 4))
		return (exec_pwd(node));
	if (!ft_strncmp(node->tokens[0], "cd", 3))
		return (exec_cd(master, node));
	if (!ft_strncmp(node->tokens[0], "export", 7))
		return (exec_export(master, node));
	if (!ft_strncmp(node->tokens[0], "unset", 6))
		return (exec_unset(master, node));
	if (!ft_strncmp(node->tokens[0], "exit", 5))
		return (exec_exit(master, node));
	if (!ft_strncmp(node->tokens[0], "echo", 5))
		return (exec_echo(node));
	//ft_printf("JEGO CON ->%s<- ->%s<-\n", check_cmd(master, node), *node->tokens);
	execve(check_cmd(master, node), node->tokens, env_to_array(master->env_list));
	print_error("ba.sh: execve error :: \n", 1);
	perror(NULL);
	return (EXIT_FAILURE);
}

static char	*check_cmd(t_master *master, t_node *node)
{
	char	*cmd;
	char	*tmp;

	cmd = node->tokens[0];
	master->path = env_get_path(master->env_list);
	if (master->path)
	{
		tmp = ft_strjoin("/\0", node->tokens[0]);
		if (!tmp)
			exit_program(ft_strdup("ba.sh: memory alloc error"), 1);
		if (check_cmd_while(master, &tmp))
			return (tmp);
		free(tmp);
	}
	if (access(cmd, F_OK) || !ft_strrchr(cmd, '/'))
		exit_program(ft_strjoin("ba.sh: ", ft_strjoin(cmd, ": command not found")), 127);
		// exit (clean_exit(pip, error_msg(PPX, cmd, CNF, 127)));
	if (access(cmd, X_OK))
		exit_program(ft_strdup("ba.sh: permission deneied"), 126);
		// exit (clean_exit(pip, error_msg(BSH, cmd, PMD, 126)));
	return (cmd);
}

//	---- private
static int	check_cmd_while(t_master *master, char **cmd)
{
	size_t	iter;
	char	*tmp;

	iter = 0;
	while (master->path[iter])
	{
		tmp = ft_strjoin(master->path[iter], *cmd);
		if (!tmp)
			exit_program(ft_strdup("ba.sh: memory alloc error"), 1);
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
				break ;
			free(tmp);
			exit_program(ft_strdup("ba.sh: permission denied"), 1);
		}
		free(tmp);
		iter++;
	}
	if (!master->path[iter])
		return (0);
	free(*cmd);
	*cmd = tmp;
	return (1);
}


