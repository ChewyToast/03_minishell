/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:36:42 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/21 16:15:21 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <unistd.h>

struct s_parse
{
	char	*start;
	char	*end;
	char	*delim;
	int8_t	type;
}	t_parse;


int		get_operator(char *str);

t_node	*create_node(t_node **list, char *start, char *end, int node_id)
{
	t_node	*new_node;
	t_node	*temp;

	if (*(end + 1) == '\0')
		end++;
	new_node = malloc (sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->node_id = node_id;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->child = NULL;
	new_node->pid = 0;
	new_node->fd[0] = 0;
	new_node->fd[1] = 0;
	new_node->subshell = false;
	if (*start == '(')
		new_node->subshell = true;
	new_node->data = ft_substr(start, 0, end - start);
	new_node->tokens = ft_split(new_node->data, ' ');
	new_node->operator = get_operator(end);
	if (*list)
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}	
	else
		*list = new_node;
	return (new_node);
}

int		get_operator(char *str)
{
	if (*str == '|' && *(str + 1) == '|')
		return (TOR);
	if (*str == '&' && *(str + 1) == '&')
		return (TAND);
	if (*str == '|' && *(str + 1) != '|')
		return (TPIP);
	if (*(str + 1) == '\0')
		return (TEND);
	return (TUNDEF);	
}

_Bool	is_operator(char *str)
{
	if (*str == '|' && *(str + 1) == '|')
		return (1);
	if (*str == '&' && *(str + 1) == '&')
		return (1);
	if (*str == '|' && *(str + 1) != '|')
		return (1);
	return (0);
}

int	get_close_bracket (char *line)
{
	int	depth;
	int	count;

	count = 0;
	depth = 0;

	while (line[count])
	{
		if (line[count] == '(')
			depth++;
		if (line[count] == ')')
			depth--;
		if (depth == 0)
			return (count);
		count++;
	}
	return (0);
}


_Bool	parser(t_node **list, char *parse_str, int reset)
{
	int		i;
	t_node	*node;
	char	*last_operator;
	static	int node_id = 0;

	if (reset)
		node_id = 0;
	i = -1;
	last_operator = parse_str;
	while (parse_str[++i])
	{
		if (is_operator(&parse_str[i]) || parse_str[i + 1] == '\0')
		{
			if (!create_node(list, last_operator, &(parse_str[i]), ++node_id))
				return (1);
			if (get_operator(&parse_str[i]) > 3)
				i++;
			last_operator = &parse_str[i + 1];
		}
		if (parse_str[i] == '(')
		{
			node = create_node(list, &parse_str[i], &parse_str[i + get_close_bracket(&parse_str[i]) + 1], ++node_id);
			if (node == NULL)
				return (1);
			if (parser (&(node->child), ft_substr(parse_str, i + 1, get_close_bracket(&parse_str[i]) - 1), 0))
				return (1);
			i = i + get_close_bracket(&parse_str[i]);	
			while (!(is_operator(&parse_str[i]) || parse_str[i + 1] == '\0'))
				i++;
			node->operator = get_operator(&parse_str[i]);
			i++;
			if (node->operator > 3)
				i++;
			last_operator = &parse_str[i + 1];
		}
	}
	free (parse_str);
	return (0);
}

