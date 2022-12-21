/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:31:31 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/21 19:33:14 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

int	main(int argc, char **argv, char **env)
{
	t_node	*node;
	t_env	*env_list;

	(void)argv;
	if (argc != 1)
		return (0);
	env_list = env_parser(env);
	while (1)
	{
		if (parser(&node, readline("\n\033[38;5;143mba.sh $ \033[0;39m"), 1))
		{
			error(node, "ba.sh: error parsing input\n");
			exit (1);
		}
		if (!ft_strncmp(node->data, "exit", 6))
			break ;
		print_parse_tree(node);
		node = free_tree(node);
	}
	node = free_tree(node);
	env_free_list(env_list);
	return (0);
}

t_node	*free_tree(t_node *node)
{
	t_node	*temp;

	while (node)
	{
		if (node->child)
			free_tree(node->child);
		temp = node->next;
		free (node->data);
		free (node);
		free_split(node->tokens);
		node = temp;
	}
	return (NULL);
}

void	error(t_node *node, char *error)
{
	printf("ERRROR: %s\n", error);
	free_tree(node);
}
