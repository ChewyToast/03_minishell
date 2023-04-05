/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:48:23 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/04 14:22:48 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "redirections.h"
#include "utils.h"

char		*init_tokenizer(char *data_in, t_master *master, bool wildcard);
char		*get_next_token(bool wildcard);

//	---- local headers
static bool	add_new_redirect(t_redirect *redirect, t_node *node);
static void	add_redirect(t_redirect *redirect, t_redirect **node);
static int	get_redirect_fd(char *start, char *end, char type);
static int	extract_redirect(char **data, t_node *node, char *promt_init,
				t_master *master);
static bool	redirect_expander(t_redirect *redirect, t_master *master);
static bool	check_are_quotes(char *data);
static char	*extractor_init(char *data, char **full_data, t_is *is);

//	---- public
char	*extract_redirects_and_clean(char *data, t_node *node, t_master *master)
{
	char	*new_data;
	char	*full_data;
	t_is	is;
	int		num_char_delete;

	new_data = extractor_init(data, &full_data, &is);
	while (*data)
	{
		if (*(data) == 92 && !is.quoted)
			is.scaped = 1;
		check_quotes(data, &is.quoted, &is.dbl_quoted);
		if (((*data) == '>' || (*data) == '<') && is_free_char(is))
		{
			new_data = ft_chrjoin(new_data, ' ');
			num_char_delete = extract_redirect(&data, node, full_data, master);
			if (num_char_delete > 0)
				new_data = ft_chrjoin(ft_substr(new_data, 0,
							ft_strlen(new_data) - num_char_delete), ' ');
		}
		else
			new_data = ft_chrjoin(new_data, *(data++));
		is.scaped = 0;
	}
	free (full_data);
	return (new_data);
}

//	---- local private
static char	*extractor_init(char *data, char **full_data, t_is *is)
{
	char	*new_data;

	*full_data = data;
	new_data = ft_strdup("");
	is->dbl_quoted = false;
	is->quoted = false;
	is->scaped = false;
	return (new_data);
}

static int	extract_redirect(char **data, t_node *node, char *promt_init,
				t_master *master)
{
	t_redirect	redirect;
	char		*end;
	char		*start;
	int			num_char_del;
	char		*symbol;

	(void) master;
	symbol = *data;
	redirect.type = get_type_redirect(data);
	if (!redirect.type)
		return (EXIT_FAILURE);
	start = get_redirect_start(symbol, promt_init);
	redirect.fd = get_redirect_fd(start, symbol, redirect.type);
	num_char_del = *data - start;
	end = get_redirect_end(*data);
	spaces_clean(data);
	redirect.raw_data = ft_substr(*data, 0, end - *data);
	redirect_expander(&redirect, master);
	*data = end;
	spaces_clean(data);
	add_new_redirect(&redirect, node);
	return (num_char_del);
}

static int	get_redirect_fd(char *start, char *end, char type)
{
	char	*value;
	int		fd;

	if (start == end)
	{
		if (type == RIN || type == RDOC)
			return (STDIN_FILENO);
		else
			return (STDOUT_FILENO);
	}
	value = ft_substr(start, 0, end - start);
	while (ft_isdigit(*start) && end > start)
		start++;
	spaces_clean(&start);
	if (start != end)
		return (-1);
	fd = ft_atoi(value);
	free(value);
	return (fd);
}

static bool	add_new_redirect(t_redirect *redirect, t_node *node)
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

static void	add_redirect(t_redirect *redirect, t_redirect **node)
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

static bool	redirect_expander(t_redirect *redirect, t_master *master)
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

static bool	check_are_quotes(char *data)
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
