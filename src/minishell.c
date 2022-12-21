/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/12/21 15:42:48 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/headers/structs.h"
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
	//print_env(env_list);
	//logtrace ("test", 1, 2, 3);
	while (1)
	{
		if (parser(&node, readline("\n\033[38;5;143mba.sh $ \033[0;39m"), 1))
		{
			error(node, "ba.sh: error parsing input\n");
			exit (1);
		}
		//executor(node);
		if (!ft_strncmp(node->data, "exit", 6))
			break;
		print_parse_tree(node);
		node = free_tree(node);
	}

	//print_env(env_list);
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

void error(t_node *node, char *error)
{
    printf("ERRROR: %s\n", error);
    free_tree(node);
}


/*
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
	return (0);
}
*/
