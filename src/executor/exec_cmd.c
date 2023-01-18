/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/18 16:31:51 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

char	**expander(char **tokens, t_master *master);

//Ejecutamos comando
// 1.- Expandimos wilcards y dolars
// 2.- Tokenizacion
// 3.- Ejecutamos en función de si es builtin o execve

int	execute_command(t_master *master, t_node *node)
{
	node->tokens = expander(node->tokens, master);
	if (is_builtin (node))
		return (execute_builtins(master, node));
	execve(check_cmd(master, node), node->tokens, env_to_array(master->env_list));
	error("ba.sh: execve error\n", 1);
	return (1);
}

char	**expander(char **tokens, t_master *master)
{
	char	**expanded_tokens;

	(void) master;
	expanded_tokens = expand_wildcard(tokens);
	return (expanded_tokens);
}

int	execute_builtins(t_master *master, t_node *node)
{
	(void)master;
	// print_env(master->env_list);
	// ft_printf("---------> HOME >%s<\n", getenv("HOME"));
	if (!ft_strncmp(node->tokens[0], "pwd", 4))
		return (exec_pwd());
	return (1);
}