/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/02/20 17:35:41 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

char	*expander(char *data, t_master *master);
char	*get_token(char **data);
char	*parse_token(char *data_in, t_master *master, int reset);

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

int	exec(t_master *master, t_node *node)
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


