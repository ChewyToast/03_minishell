/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:19:24 by ailopez-          #+#    #+#             */
/*   Updated: 2023/01/17 16:09:21 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/time.h>

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
		printf("%s >> SUBSHELL << %s %s %s", U_ORANGE, GRAY,
			node->data, DEF_COLOR);
	else
	{
		printf("%s %s %s", U_BLUE, node->data, DEF_COLOR);
		j = -1;
		while (node->tokens[++j])
			printf("%s [%s] %s", U_YELLOW, node->tokens[j], DEF_COLOR);
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

void	logtrace(char	*str1, char *str2, int param1, int param2)
{
	struct timeval	time;
	unsigned int	t[2];
	static int		init = 1;
	FILE			*file;
	static sem_t	*sem_log = NULL;

	if (init)
	{
		init = 0;
		sem_unlink("sem_logger");
		sem_log = sem_open("sem_logger", O_CREAT | O_EXCL, 0644, 1);
		sem_wait(sem_log);
		file = fopen("log.txt", "w");
	}
	else
	{
		sem_wait(sem_log);
		file = fopen("log.txt", "a");
	}
	gettimeofday(&time, NULL);
	t[0] = (time.tv_sec & 0xFFFF);
	t[1] = (time.tv_usec / 1000);
	fprintf(file, "[%d::%d]---[%s---[%s]---[%d]---[%d]\n", \
			t[0], t[1], str1, str2, param1, param2);
	fclose (file);
	sem_post(sem_log);
}
