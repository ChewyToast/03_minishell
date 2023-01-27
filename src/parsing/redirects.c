#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <unistd.h>

bool	add_new_redirect(char *data, int type, t_node *node);
int		get_type_redirect(char **data);
char	*get_redirect_end(char *data);


char	*extract_redirects_and_clean(char *data, t_node *node)
{
	char	*new_data;
	char	*full_data;
	bool	is_quoted;
	bool	is_dbl_quoted;

	full_data = data;
	new_data = ft_strdup("");
	if (new_data == NULL)
		return (NULL);
	while (*data)
	{
		if (*(data) == 92 && !is_quoted)
		{
			new_data = ft_chrjoin(new_data, *(++data));
			data++;
		}
		if ((*data) == 39)
		{
			is_quoted = !is_quoted;
			data++;
		}
		else if ((*data) == 34)
		{
			is_dbl_quoted = !is_dbl_quoted;
			data++;
		}
		else if (((*data) == '>' || (*data) == '<') && !is_quoted && !is_dbl_quoted)
			extract_redirect(&data, node);
		else
			new_data = ft_chrjoin(new_data, *(data++));
	}
	free (full_data);
	return (new_data);

}

bool extract_redirect(char **data, t_node *node)
{
	int		type;
	char	*redirect;
	char	*aux;
	
	spaces_clean(data);
	type = get_type_redirect(data);
	if (!type)
		return (EXIT_FAILURE);
	spaces_clean(data);
	aux =  get_redirect_end(*data);
	redirect = ft_substr(*data, 0, aux - *data);
	*data = aux ;
	spaces_clean(data);
	return (add_new_redirect(redirect, type, node));
}


int	get_type_redirect(char **data)
{
	if(**data == '<')
	{
		(*data)++;
		return	(RIN);
	}
	else if(**data == '>')
	{
		(*data)++;
		if(**data && **data == '>')
			return (RADD);
		else
			return (ROUT);
	}
	else
		return (0);
}

bool is_redirect_limit(char c)
{
	if (c == '>')
		return (true);
	if (c == '<')
		return (true);
	if (c == ' ')
		return (true);
	if (c == '\0')
		return (true);
	return (false);
}

char	*get_redirect_end(char *data)
{
	bool	is_quoted;
	bool	is_dbl_quoted;

	is_quoted = 0;
	is_dbl_quoted = 0;
	while (*data)
	{
		if (*(data) == 92)
		{
			data++;
			if (*data)
				data++;
		}	
		if ((*data) == 39)
		{
			is_quoted = !is_quoted;
			data++;
		}
		else if ((*data) == 34)
		{
			is_dbl_quoted = !is_dbl_quoted;
			data++;
		}	
		else if (is_redirect_limit(*data) && !is_quoted && !is_dbl_quoted)
			return (data);
		data++;
	}
	return (data);
}

bool	add_new_redirect(char *data, int type, t_node *node)
{
	t_redirect	*new_redirect;

	new_redirect = malloc (sizeof (t_redirect));
	if (new_redirect == NULL)
		return (EXIT_FAILURE);
	new_redirect->type = type;
	new_redirect->data = ft_strdup(data);
	free (data);
	new_redirect->next = NULL;
	if (!node->redirects)
		node->redirects = new_redirect;
	else
	{
		while (node->redirects->next)
			node->redirects = node->redirects->next;
		node->redirects->next = new_redirect;
	}
	return (EXIT_SUCCESS);
}

