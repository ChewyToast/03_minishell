/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:19:24 by ailopez-          #+#    #+#             */
/*   Updated: 2022/12/15 14:10:56 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

void	free_split(char	**split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	free (split);
}

t_node	*new_node(t_node *top)
{
	static int	node_id = 0;
	t_node		*node;

	node_id++;
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->node_id = node_id;
	node->top = top;
	node->left = NULL;
	node->right = NULL;
	node->type = 0;
	node->start = NULL;
	node->end = NULL;
	node->redirect = NULL;
	return (node);
}

t_node	*hardcode_tree()
{
	t_node *tree;

	tree = new_node(NULL);
	tree->left = new_node(tree);
	tree->right = new_node(tree);
	tree->left->right = new_node(tree->left);
	tree->left->left = new_node(tree->left);
	tree->right->right = new_node(tree->right);
	tree->right->left = new_node(tree->right);
	return (tree);
}

void	print_data(char *start, char *end)
{
	(void) end;
	printf ("%s", start);
}


void print_node_type(int type)
{
	if (type == 0)
		printf("NULL \t ");
	else if (type == TAND)
		printf("AND \t ");
	else if (type == TOR)
		printf("OR \t ");
	else if (type == TUNDEF)
		printf("UNDEF \t ");
	else if (type == TPIP)
		printf("TPIP \t ");
	else if (type == TCMD)
		printf("CMD \t ");
	else
		printf("--- \t ");
}

void	print_node(t_node *node)
{
	int	node_right;
	int	node_left;
	int	node_top;
	
	node_right = 0;
	if (node->right)
		node_right = node->right->node_id;
	node_left = 0;
	if (node->left)
		node_left = node->left->node_id;
	node_top = 0;
	if (node->top)
		node_top = node->top->node_id;		

	printf ("-----------------------------------------------------------------------------------------------------------\n");
	printf("Node [%d] \t", node->node_id);
	printf("Left [%d] \t", node_left);
	printf("Right [%d] \t", node_right);
	printf("Top [%d] \t", node_top);	
	print_node_type(node->type);
	print_data(node->start, node->end);
	printf("\n");
}

void print_tree_nodes(t_node *node)
{
	if (node->right)
        print_tree_nodes(node->right);
    if (node->left)
        print_tree_nodes(node->left);
    if (!node->right && !node->right)
        print_node (node);
    else
        print_node (node);
}


void print_tree(t_node *node)
{
	printf ("\n\n********************************************************************************************************************\n\n");
	printf ("NODE ID \tLEFT NODE \tRIGHT NODE \tTOP NODE \tTYPE \tDATA\n");
	printf ("\n********************************************************************************************************************\n\n");		
	print_tree_nodes (node);
	printf ("\n********************************************************************************************************************\n\n");		
}