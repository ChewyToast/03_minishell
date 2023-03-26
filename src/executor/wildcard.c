/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:50:32 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/26 18:16:28 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

//	---- local headers
static	bool	match_wildcard(char *s, char *pattern);
static	void	step_forward(char **pattern, char **s);

//	---- public
char	*expand_str_wildcard(char *token)
{
	char	*to_expand;
	char	*base_path;
	char	*new_str;
	t_files	*files;
	t_files	*temp;
	bool	is_match;

	is_match = 0;
	to_expand = get_no_path(token);
	base_path = get_base_path(token);
	files = list_dir_files(base_path);
	free (base_path);
	new_str = ft_strdup("");
	while (files)
	{
		if (match_wildcard(files->file, to_expand))
		{
			if (is_match)
				new_str = ft_strjoin_free (new_str, ft_strdup(" "));
			new_str = ft_strjoin_free (new_str, ft_strdup(files->file));
			is_match = 1;
		}
		temp = files;
		files = files->next;
		free(temp->file);
		free(temp);
	}
	free(to_expand);
	if (!is_match)
	{
		free(new_str);
		return (ft_strdup(token));
	}
	return (new_str);
}

static	bool	match_wildcard(char *s, char *pattern)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (true);
			while (*s)
			{
				if (match_wildcard(s, pattern))
					return (true);
				s++;
			}
			return (false);
		}
		else if (*pattern == '?')
			step_forward(&pattern, &s);
		else if (*pattern == *s)
			step_forward(&pattern, &s);
		else
			return (false);
	}
	return (!*s);
}

static	void	step_forward(char **pattern, char **s)
{
	(*pattern)++;
	(*s)++;
}
