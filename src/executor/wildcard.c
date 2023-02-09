/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:50:32 by ailopez-          #+#    #+#             */
/*   Updated: 2023/02/07 19:51:23 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

void		free_file_list(t_files *files);
char		*ft_strjoin_free(char	*str1, char	*str2);

/*-------------------------- PUBLIC SECTION ------------------------------*/

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

/*-------------------------- PRIVATE SECTION ------------------------------*/

void	free_file_list(t_files *files)
{
	t_files	*temp;
	
	while (files)
	{
		temp = files;
		files = files->next;
		free(temp->file);
		free(temp);
	}
}