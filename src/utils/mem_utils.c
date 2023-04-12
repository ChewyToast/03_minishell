/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:54:37 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/12 14:41:14 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (ft_calloc(size, 1));
	if (!size)
		return (ptr);
	new_ptr = ft_calloc(size, 1);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

t_node	*free_tree(t_node *node)
{
	t_node		*temp;
	t_redirect	*tmp_redir;

	while (node)
	{
		if (node->child)
			free_tree(node->child);
		temp = node->next;
		if (node->data)
			free (node->data);
		while (node->redirects)
		{	
			tmp_redir = node->redirects->next;
			free(node->redirects->data);
			free(node->redirects->raw_data);
			free(node->redirects);
			node->redirects = tmp_redir;
		}
		if (node->tokens)
			free_split(node->tokens);
		free (node);
		node = temp;
	}
	return (NULL);
}

int	free_split(char	**split)
{
	int	i;

	if (!split)
		return (1);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free (split);
	return (1);
}

long	ft_atoi_long_long(const char *nptr)
{
	long long	num;
	int			symb;

	num = 0;
	symb = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		symb = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= 48 && *nptr <= 57)
	{
		num *= 10;
		num = num + (*nptr - 48);
		nptr++;
	}
	return (num * symb);
}
