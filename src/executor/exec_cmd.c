/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/26 17:51:30 by bmoll-pe         ###   ########.fr       */
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

int	prepare_exec(t_master *master, t_node *node)
{
	// node->tokens = expander(node->tokens, master);
	// node->tokens = tokenizer(node->data);
	return (exec(master, node));
}

char	**expander(char **tokens, t_master *master)
{
	char	**expanded_tokens;

	(void) master;
	expanded_tokens = expand_wildcard(tokens);
	return (expanded_tokens);
}

int	exec(t_master *master, t_node *node)
{
	if (!ft_strncmp(node->tokens[0], "pwd", 4))
		return (exec_pwd(node));
	if (!ft_strncmp(node->tokens[0], "cd", 3))
		return (exec_cd(master, node));
	if (!ft_strncmp(node->tokens[0], "export", 3))
		return (exec_export(master, node));
	if (!ft_strncmp(node->tokens[0], "unset", 3))
		return (exec_unset(master, node));
	if (!ft_strncmp(node->tokens[0], "exit", 3))
		return (exec_exit(master, node));
	// ft_printf("JEGO CON ->%s<- ->%s<-\n", check_cmd(master, node), *node->tokens);
	execve(check_cmd(master, node), node->tokens, env_to_array(master->env_list));
	error("ba.sh: execve error\n", 1);
	return (1);
}