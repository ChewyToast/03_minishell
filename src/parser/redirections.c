/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:48:23 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/06 13:44:12 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

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
char	*extractor_init(char *data, char **full_data, t_is *is)
{
	char	*new_data;

	*full_data = data;
	new_data = ft_strdup("");
	is->dbl_quoted = false;
	is->quoted = false;
	is->scaped = false;
	return (new_data);
}

int	extract_redirect(char **data, t_node *node, char *promt_init,
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

int	get_redirect_fd(char *start, char *end, char type)
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
