/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:50:32 by ailopez-          #+#    #+#             */
/*   Updated: 2023/01/11 02:50:53 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

static char	**expand_token(char *token);
static char	**token_join(char **expanded, char *token, int *num_new_tokens);
static char	**expander(t_files *files, char *to_expand);
static bool	is_expanded(char *arg);

/*-------------------------- PUBLIC SECTION ------------------------------*/

char	**expand_wildcard(char **tokens)
{
	char	**expanded;
	int		i;
	int		num_token;

	expanded = ft_calloc(sizeof(char *), 2);
	if (!expanded)
		return (NULL);
	expanded[0] = ft_strdup(tokens[0]);
	num_token = 1;
	i = 0;
	while (tokens[++i])
	{
		if (is_expanded(tokens[i]))
			expanded = token_join (expanded, tokens[i], &num_token);
		else
		{
			expanded = ft_realloc(expanded, (num_token + 2) * sizeof(char *));
			if (!expanded)
				return (NULL);
			expanded[num_token++] = ft_strdup(tokens[i]);
		}
	}
	expanded[num_token] = NULL;
	free_split(tokens);
	return (expanded);
}

/*-------------------------- PRIVATE SECTION ------------------------------*/

static char	**token_join(char **expanded, char *token, int *num_new_tokens)
{
	int		num_sub_tokens;
	char	**sub_tokens;

	sub_tokens = expand_token(token);
	if (!sub_tokens)
		return (NULL);
	num_sub_tokens = 0;
	while (sub_tokens[num_sub_tokens])
	{
		expanded = ft_realloc(expanded, (*num_new_tokens + 2) * sizeof(char *));
		if (!expanded)
			return (NULL);
		expanded[*num_new_tokens] = sub_tokens[num_sub_tokens];
		(*num_new_tokens)++;
		num_sub_tokens++;
	}
	free(sub_tokens);
	return (expanded);
}

static char	**expand_token(char *token)
{
	char	**expanded;
	char	*to_expand;
	char	*base_path;
	t_files	*files;

	to_expand = get_no_path(token);
	base_path = get_base_path(token);
	files = list_dir_files(base_path);
	free (base_path);
	if (!files)
		return (NULL);
	expanded = expander (files, to_expand);
	free (to_expand);
	return (expanded);
}

static char	**expander(t_files *files, char *to_expand)
{
	int		num_files;
	char	**expanded;
	t_files	*temp;

	num_files = 0;
	expanded = ft_calloc(sizeof(char *), 1);
	if (!expanded)
		return (NULL);
	while (files)
	{
		if (match_wildcard(files->file, to_expand))
		{
			expanded = ft_realloc(expanded, (num_files + 2) * sizeof(char *));
			if (!expanded)
				return (NULL);
			expanded[num_files] = files->file;
			num_files++;
		}
		temp = files;
		files = files->next;
		free(temp);
	}
	expanded[num_files] = NULL;
	return (expanded);
}

static bool	is_expanded(char *arg)
{
	if (ft_strchr (arg, '*') || ft_strchr (arg, '?'))
		return (true);
	else
		return (false);
}
