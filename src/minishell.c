/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:06:45 by bruno             #+#    #+#             */
/*   Updated: 2022/12/19 11:04:58 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

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
		if (init_node(&node, 0))
			return (1);
		if (!node || parser(node, readline("\nba.sh $ "), NULL))
		{
			error(node, "ba.sh: error parsing input\n");
			exit (1);
		}
		print_tree(node);
		free_tree(node);
	}
	print_env(env_list);
	env_free_list(env_list);
	return (0);
}

void    free_tree(t_node *node)
{
    if (node->right)
        free_tree(node->right);
    if (node->left)
        free_tree(node->left);
    if (!node->right && !node->right)
        free (node);
    else
        free (node);
}

void error(t_node *node, char *error)
{
    printf("ERRROR: %s\n", error);
    free_tree(node);
}

_Bool	init_node(t_node **node, int mode)
{
	static int node_id = 0;

	if (!mode)
		node_id = 0;
	else
		node_id ++;
	*node = malloc(sizeof(t_node));
	if (!*node)
		return (1);
	(*node)->node_id = node_id; 
	(*node)->type = 0;
	(*node)->start = NULL;
	(*node)->end = NULL;
	(*node)->top = NULL;
	(*node)->right = NULL;
	(*node)->left = NULL;
	(*node)->redirect = NULL;
	printf ("Node created [%d]\n", node_id);
	return (0);
}
