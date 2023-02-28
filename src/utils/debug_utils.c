/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:19:24 by ailopez-          #+#    #+#             */
/*   Updated: 2023/02/28 22:54:43 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

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
			printf("%sFD[%d]", U_MAG, node->redirects->fd);
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

void	add_bash_lvl(t_master *master, t_env *node)
{
	int	value;

	if (!node)
		return ;
	value = ft_atoi(node->value);
	value += 1;
	master->shlv = value;
	free(node->value);
	node->value = ft_itoa(value);
	if (node->value)
		return ;
	free_tree(master->node);
	env_free_list(master->env_list);
	write(2, "ba.sh: memory error\n", 20);
}

void	default_env(t_master *master)
{
	char	*buff;

	buff = ft_calloc(PATH_MAX + 1, 1);
	if (env_new_value(&master->env_list, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."))
		exit (1);// ERROR!!
	if (env_new_value(&master->env_list->next, "SHLVL", "1"))
		exit (1);// ERROR!!
	if (!getcwd(buff, PATH_MAX))
		exit_program(ft_strdup("ba.sh: Error trying to allocate memory"), 1);// ERROR!!!!
	if (env_new_value(&master->env_list->next->next, "PWD", buff))
		exit (1);// ERROR!!
	if (env_new_value(&master->env_list->next->next->next, "_", "/usr/bin/env"))
		exit (1);// ERROR!!
	free(buff);
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


int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	str_to_lower(char *str)
{
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}

}