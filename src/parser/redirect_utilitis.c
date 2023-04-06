/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utilitis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:41:26 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:45:49 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

bool	add_new_redirect(t_redirect *redirect, t_node *node)
{
	t_redirect	*new_redirect;

	new_redirect = malloc (sizeof (t_redirect));
	if (new_redirect == NULL)
		return (EXIT_FAILURE);
	new_redirect->type = redirect->type;
	new_redirect->data = ft_strdup(redirect->data);
	new_redirect->fd = redirect->fd;
	new_redirect->hdoc_is_quoted = redirect->hdoc_is_quoted;
	new_redirect->next = NULL;
	add_redirect(new_redirect, &node->redirects);
	return (EXIT_SUCCESS);
}

void	add_redirect(t_redirect *redirect, t_redirect **node)
{
	t_redirect	*redirect_ini;

	if (!*node)
		*node = redirect;
	else
	{
		redirect_ini = *node;
		while ((*node)->next)
			*node = (*node)->next;
		(*node)->next = redirect;
		*node = redirect_ini;
	}
}

bool	redirect_expander(t_redirect *redirect, t_master *master)
{
	char	*token;

	redirect->data = ft_strdup("");
	if (redirect->type == RDOC)
		redirect->hdoc_is_quoted = check_are_quotes(redirect->raw_data);
	if (ft_strlen(redirect->raw_data) == 1 && redirect->raw_data[0] == '~'
		&& redirect->raw_data[1] == '\0')
	{
		free(redirect->raw_data);
		redirect->raw_data = ft_strdup(" ~ ");
	}
	token = init_tokenizer(redirect->raw_data, master, WILDCARD_OFF);
	while (token)
	{
		redirect->data = ft_strjoin_free(redirect->data, token);
		token = get_next_token(WILDCARD_OFF);
	}
	return (true);
}

bool	check_are_quotes(char *data)
{
	while (*data)
	{
		if (*data == 92)
			data++;
		else if (*data == '\'' || *data == '\"')
			return (true);
		data++;
	}
	return (false);
}
