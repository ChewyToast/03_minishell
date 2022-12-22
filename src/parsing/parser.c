/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:36:42 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/22 22:31:18 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <unistd.h>

t_node	*create_node(t_node **list, char *start, char *end, int node_id);
int		get_close_bracket(char *line);
int		get_operator(char *str);
_Bool	is_operator(char *str);
ssize_t	ffwd(char *start);
int		isquote(char *str, char quote);
int		isscaped(char *str);

_Bool	parser(t_node **list, char *parse_str, int reset)
{
	ssize_t		i;
	t_node		*node;
	char		*last_operator;
	static int	node_id = 0;
	
	if (reset)
		node_id = 0;
	if (!parse_str)
		return (1);
	i = 0;
	last_operator = parse_str;
	while (parse_str[i])
	{
		i += ffwd(&parse_str[i]);
		if (get_operator(&parse_str[i]))
		{
			if (!create_node(list, last_operator, &(parse_str[i]), ++node_id))
				return (1);
			if (get_operator(&parse_str[i]) > TCOL)
				i++;
			if (parse_str[i])
				i++;
			last_operator = &parse_str[i + 1];
		}
		else if (parse_str[i] == '(')
		{
			node = create_node(list, &parse_str[i], &parse_str[i
					+ get_close_bracket(&parse_str[i]) + 1], ++node_id);
			if (node == NULL)
				return (1);
			if (parser (&(node->child), ft_substr(parse_str, i + 1,
						get_close_bracket(&parse_str[i]) - 1), 0))
				return (1);
			i += get_close_bracket(&parse_str[i]);
			i += ffwd(&parse_str[i]);
			node->operator = get_operator(&parse_str[i]);
			i++;
			if (node->operator > TCOL)
				i++;
			last_operator = &parse_str[i + 1];
		}
		if (!parse_str[i])
			break ;
	}
	free (parse_str);
	return (0);
}

ssize_t	ffwd(char *start)
{
	size_t	count;

	count = 0;
	while (start[count] && !get_operator(&start[count]))
	{
		while (start[count] && ft_isspace(start[count]))
			count++;
		if (!start[count] || get_operator(&start[count])
			|| (start[count] == '(' && !isscaped(&start[count])))
			break ;
		if (isquote(&start[count], 34))
			while (start[count] && !isquote(&start[count], 34))
				count += 1;
		else if (isquote(&start[count], 39))
			while (&start[count] && !isquote(&start[count], 39))
				count += 1;
		if (start[count])
			count++;
	}
	return (count);
}

int	isquote(char *str, char quote)
{
	if (!str || !*str)
		return (0);
	if (*str != quote)
		return (0);
	if (!isscaped(str))
		return (*str);
	return (0);
}

int	isscaped(char *str)
{
	size_t	count;

	count = 0;
	if (*(str - 1))
		str--;
	else
		return (0);
	while (*(str - count) && *(str - count) == 92)
		count++;
	if (count % 2)
		return (*(str + 1));
	return (0);
}

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

int	get_operator(char *str)
{
	if (!*str)
		return (TEND);
	if (*str == '|' && *(str + 1) && *(str + 1) == '|'
		&& !isscaped(str))
		return (TOR);
	if (*str == '&' && *(str + 1) && *(str + 1) == '&'
		&& !isscaped(str))
		return (TAND);
	if (*str == '|' && (!*(str + 1) || *(str + 1) != '|')
		&& !isscaped(str))
		return (TPIP);
	return (TUNDEF);
}

int	get_close_bracket(char *line)
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
