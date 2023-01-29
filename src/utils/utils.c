/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:19:24 by ailopez-          #+#    #+#             */
/*   Updated: 2023/01/29 15:02:01 by aitoraudica      ###   ########.fr       */
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
#include <limits.h>

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
			printf("%s %s", U_MAG, ">");
		if (node->redirects->type == RADD)
			printf("%s %s", U_MAG, ">>");
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

void	free_split(char	**split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
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

int	is_numeric(char *inp)
{
	while(inp)
	{
		if (!ft_isdigit(*inp) && !ft_isspace(*inp))
			return (0);
		inp++;
	}
	return (1);
}

void	add_bash_lvl(t_master *master, t_env *node)
{
	int	value;

	if (!node)
		return ;
	value = ft_atoi(node->value);
	value += 1;
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
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	if (env_new_value(&master->env_list->next->next, "PWD", buff))
		exit (1);// ERROR!!
	if (env_new_value(&master->env_list->next->next->next, "_", "/usr/bin/env"))
		exit (1);// ERROR!!
	free(buff);
}

char	*ft_strjoin_free(char	*str1, char	*str2)
{
	char	*new_str;

	new_str = ft_strjoin(str1, str2);
	free (str1);
	free (str2);
	return (new_str);
}

char	*ft_chrjoin(char	*str, char	c)
{
	char	*new_str;
	char	*return_ptr;
	char	*free_ptr;
	int		len;

	len = ft_strlen(str);
	new_str = malloc((len + 2) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	return_ptr = new_str;
	free_ptr = str;
	while(*str)
		*(new_str++) = *(str++);
	*(new_str++) = c;
	*(new_str) = '\0';
	free(free_ptr);
	return (return_ptr);
}

void	spaces_clean(char **data)
{
	while (ft_isspace(**data) && **data != '\0')
		(*data)++;
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
