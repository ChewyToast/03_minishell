/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/26 19:31:29 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

char	*expander(char *data, t_master *master);
char	*get_token(char **data);

int	execute_command(t_master *master, t_node *node)
{
	char	*data;
	int		num_tokens;	

	data = node->data;
	num_tokens = 0;
	node->tokens = malloc (sizeof (char *));
	if (node->tokens == NULL)
		return (EXIT_FAILURE);
	while (data)
	{
		node->tokens[num_tokens] = expander(get_token(&data), master);
		num_tokens++;
		node->tokens = ft_realloc (node->tokens, sizeof(char *) * (num_tokens + 1));
		if (node->tokens == NULL)
			return (EXIT_FAILURE);
	}
	node->tokens[num_tokens] = NULL;
	return (exec(master, node));
}

char	*get_token(char **data)
{
	(void) data;
	return (NULL);
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


