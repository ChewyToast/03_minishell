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

static	char	*clean_data(char *data, int nchr_del);

//	---- public
char	*extract_redirects_and_clean(char *data, t_node *node, t_master *master)
{
	char	*new_data;
	char	*full_data;
	t_is	is;
	int		nchr_del;

	new_data = extractor_init(data, &full_data, &is);
	while (*data)
	{
		if (*(data) == 92 && !is.quoted)
			is.scaped = 1;
		check_quotes(data, &is.quoted, &is.dbl_quoted);
		if (((*data) == '>' || (*data) == '<') && is_free_char(is))
		{
			new_data = ft_chrjoin(new_data, ' ');
			nchr_del = 0;
			nchr_del = extract_redirect(&data, node, full_data, master);
			if (nchr_del > 0)
				new_data = clean_data(new_data, nchr_del);
		}
		else
			new_data = ft_chrjoin(new_data, *(data++));
		is.scaped = 0;
	}
	free (full_data);
	return (new_data);
}

//	---- local private
static	char	*clean_data(char *data, int nchr_del)
{
	char	*new_data;
	char	*tmp_data;

	tmp_data = ft_substr(data, 0, ft_strlen(data) - nchr_del);
	free(data);
	new_data = ft_chrjoin(tmp_data, ' ');
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

	symbol = *data;
	redirect.type = get_type_redirect(data);
	if (!redirect.type)
		return (EXIT_FAILURE);
	start = get_redirect_start(symbol, promt_init);
	redirect.fd = get_redirect_fd(start, symbol, redirect.type);
	num_char_del = *data - start;
	if (redirect.type == RADD || redirect.type == RDOC)
		num_char_del --;
	end = get_redirect_end(*data);
	spaces_clean(data);
	redirect.raw_data = ft_substr(*data, 0, end - *data);
	redirect_expander(&redirect, master);
	*data = end;
	spaces_clean(data);
	add_new_redirect(&redirect, node);
	free(redirect.raw_data);
	free(redirect.data);
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
	if (type == RDOC)
		return (0);
	return (fd);
}
