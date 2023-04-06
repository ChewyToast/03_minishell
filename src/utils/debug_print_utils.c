/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:47:32 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:50:01 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "env.h"
#include "utils.h"

char	*node_operator_str(t_node *node);

void	print_redirects(t_node *node)
{
	t_redirect	*tmp;

	tmp = node->redirects;
	while (node->redirects)
	{
		printf("%s :: FD[%d]", U_MAG, node->redirects->fd);
		if (node->redirects->type == RIN)
			printf("%s %s", U_MAG, "<");
		if (node->redirects->type == ROUT)
			printf("%s", ">");
		if (node->redirects->type == RADD)
			printf("%s", ">>");
		if (node->redirects->type == RDOC)
			printf("%s %s", U_MAG, "<<");
		printf("[%s] %s", node->redirects->data, DEF_COLOR);
		printf(" ");
		node->redirects = node->redirects->next;
	}
	node->redirects = tmp;
}

void	print_node(t_node *node, int indent)
{
	char	*str_node_operator;
	int		i;
	int		j;

	str_node_operator = node_operator_str(node);
	i = -1;
	while (++i < indent)
		printf(" ");
	printf("|-%s[%d]%s", KCYN, node->node_id, DEF_COLOR);
	if (node->subshell)
	{
		printf("%s >> SUBSHELL << %s %s %s", U_ORANGE, GRAY,
			node->data, DEF_COLOR);
	}
	else
	{
		printf("%s %s %s", U_BLUE, node->data, DEF_COLOR);
		j = -1;
		if (node->tokens)
			while (node->tokens[++j])
				printf("%s [%s] %s", U_YELLOW, node->tokens[j], DEF_COLOR);
	}		
	print_redirects(node);
	printf("%s[%s]%s\n\n", GREEN, str_node_operator, DEF_COLOR);
	free(str_node_operator);
}

void	print_tree_nodes(t_node *node, int level)
{
	if (node == NULL)
		return ;
	while (node)
	{
		print_node(node, level);
		if (node->child)
			print_tree_nodes(node->child, level + 5);
		node = node->next;
	}
}

void	print_parse_tree(t_node *node)
{
	printf("\n");
	printf("\n");
	print_tree_nodes (node, 2);
	printf("\n");
	printf("\n");
}
