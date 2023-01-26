/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/26 17:35:03 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

char	*expand_data(char *data, t_node *node, t_master *master);

int	execute_command(t_master *master, t_node *node)
{
	char	*expanded_data;

	expanded_data = expand_data(node->data, node, master);
	//expanded_data = extract_redirects(expanded_data, node);
	// ------------/ DEBUG
	printf("%s >> Expanded data :: %s [%s]\n", U_ORANGE, DEF_COLOR, expanded_data);
	//node->tokens = tokenizer(expanded_data);
	//node->tokens = get_tokens(expanded_data);
	free (expanded_data);
	// ------------/ DEBUG	
	print_parse_tree(node);	
	if (is_builtin (node))
		return (execute_builtins(master, node));
	execve(check_cmd(master, node), node->tokens, env_to_array(master->env_list));
	perror("error");
	error("ba.sh: execve error\n", 1);
	return (EXIT_FAILURE);
}

int	execute_builtins(t_master *master, t_node *node)
{
	(void)master;
	// print_env(master->env_list);
	// ft_printf("---------> HOME >%s<\n", getenv("HOME"));
	if (!ft_strncmp(node->tokens[0], "pwd", 4))
		return (exec_pwd());
	if (!ft_strncmp(node->tokens[0], "cd", 3))
		return (exec_cd(master, node));
	return (1);
}


