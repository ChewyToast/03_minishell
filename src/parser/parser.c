/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:36:42 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/03/12 20:12:10 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "parser_utils.h"
#include "utils.h"
#include "redirections.h"

//	---- local headers
static t_node	*create_node(t_node **list, char *start, char *end,
					t_master *master);
static void		insert_node(t_node **list, t_node *new_node);
static ssize_t	ffwd(char *start);
static t_node	*parse_subshell(int *i, char *parse_str, t_node **list,
					t_master *master);

//	---- public
bool	parser(t_node **list, char *parse_str, t_master *master)
{
	t_node	*node;
	int		i;
	char	*last_operator;

	i = 0;
	last_operator = parse_str;
	while (parse_str[i])
	{
		i += ffwd(&parse_str[i]);
		if (get_operator(&parse_str[i]))
			node = create_node(list, last_operator, &(parse_str[i]), master);
		else if (parse_str[i] == '(')
			node = parse_subshell(&i, parse_str, list, master);
		if (node == NULL)
			return (EXIT_FAILURE);
		if (node->operator > TCOL)
				i++;
		if (parse_str[i])
				i++;
		if (!parse_str[i])
			break ;
		last_operator = &parse_str[i];
	}
	return (EXIT_SUCCESS);
}

static t_node	*parse_subshell(int *i, char *parse_str, t_node **list,
					t_master *master)
{
	ssize_t		end_node;
	t_node		*node;

	end_node = *i + get_close_bracket(&parse_str[*i]) + 1;
	while (!get_operator(&parse_str[end_node]))
		end_node++;
	node = create_node(list, &parse_str[*i], &parse_str[end_node], master);
	if (node == NULL || parser(&(node->child), ft_substr(parse_str, *i + 1,
				get_close_bracket(&parse_str[*i]) - 1), master))
		return (NULL);
	*i += get_close_bracket(&parse_str[*i]);
	*i += ffwd(&parse_str[*i]);
	return (node);
}

//	---- private
static ssize_t	ffwd(char *start)
{
	char	quote;
	size_t	count;

	count = 0;
	quote = 0;
	while (start[count] && !get_operator(&start[count]))
	{
		while (start[count] && ft_isspace(start[count]))
			count++;
		if (!start[count] || get_operator(&start[count])
			|| (start[count] == '(' && !isscaped(&start[count])))
			break ;
		if (isquote(&start[count], 34) | isquote(&start[count], 39))
		{
			quote = start[count];
			count += 1;
			while (start[count] && !isquote(&start[count], quote))
				count += 1;
		}
		if (start[count])
			count++;
	}
	return (count);
}

static t_node	*create_node(t_node **list, char *start, char *end,
				t_master *master)
{
	t_node	*new_node;
	char	*raw_data;

	if (*(end + 1) == '\0')
		end++;
	new_node = malloc (sizeof(t_node));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_node));
	new_node->node_id = 0;
	new_node->subshell = false;
	if (*start == '(')
		new_node->subshell = true;
	raw_data = ft_substr(start, 0, end - start);
	start = start + get_close_bracket(start) + 1;
	if (new_node->subshell)
		raw_data = ft_substr(start, 0, end - start);
	new_node->data = extract_redirects_and_clean(raw_data, new_node, master);
	new_node->operator = get_operator(end);
	insert_node (list, new_node);
	return (new_node);
}

static void	insert_node(t_node **list, t_node *new_node)
{
	t_node	*temp;

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
}
