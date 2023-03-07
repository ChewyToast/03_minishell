/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:19:24 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/05 10:40:13 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "env.h"
#include "utils.h"

char	*node_operator_str(t_node *node)
{
	char	*operator;

	if (node->operator == TEND)
		operator = ft_strdup("END");
	else if (node->operator == TUNDEF)
		operator = ft_strdup("UNDEF");
	else if (node->operator == TPIP)
		operator = ft_strdup("PIPE");
	else if (node->operator == TCOL)
		operator = ft_strdup("COL");
	else if (node->operator == TOR)
		operator = ft_strdup("OR");
	else if (node->operator == TAND)
		operator = ft_strdup("AND");
	else
		operator = ft_strdup("----");
	return (operator);
}

void	print_redirects(t_node *node)
{
	while (node->redirects)
	{
		if (node->redirects->type == RIN)
			printf("%s %s", U_MAG, "<");
		if (node->redirects->type == ROUT)
		{
			printf("%s :: FD[%d]", U_MAG, node->redirects->fd);
			printf("%s", ">");
		}
		if (node->redirects->type == RADD)
		{
			printf("%s :: FD[%d]", U_MAG, node->redirects->fd);
			printf("%s", ">>");
		}
		if (node->redirects->type == RDOC)
			printf("%s %s", U_MAG, "<<");
		printf("[%s] %s", node->redirects->data, DEF_COLOR);
		printf(" ");
		node->redirects = node->redirects->next;
	}
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
	printf("|-");
	printf("%s[%d]%s", KCYN, node->node_id, DEF_COLOR);
	if (node->subshell)
	{
		printf("%s >> SUBSHELL << %s %s %s", U_ORANGE, GRAY,
			node->data, DEF_COLOR);
		print_redirects(node);
	}
	else
	{
		printf("%s %s %s", U_BLUE, node->data, DEF_COLOR);
		j = -1;
		if (node->tokens)
		{
			while (node->tokens[++j])
				printf("%s [%s] %s", U_YELLOW, node->tokens[j], DEF_COLOR);
		}
		print_redirects(node);
	}		
	printf("%s[%s]%s", GREEN, str_node_operator, DEF_COLOR);
	printf("\n");
	printf("\n");
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


int	is_numeric(char *inp)
{
	while(*inp && ft_isdigit(*inp))
		inp++;
	if (*inp)
		return (0);
	return (1);
}


char	*total_trim(char *data, char c)
{

	char	*new_data;
	spaces_clean(&data);
	new_data = ft_strdup("");
	while (*data)
	{
		while ((*data != c && *data) && new_data)
			new_data = ft_chrjoin(new_data, *(data++));
		spaces_clean(&data);
		if (!*data)
			break;
		data--;
		new_data = ft_chrjoin(new_data, *(data++));
	}
	return (new_data);
}
