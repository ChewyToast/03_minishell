/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:57:55 by ailopez-          #+#    #+#             */
/*   Updated: 2023/01/11 03:00:59 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <dirent.h>

bool	add_file_list(t_files **file_list, char	*file);

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Get ONLY the file or last directory name of the path
| ----/ Params:	path
| ----/ Return:	New malloced string with the result
*----------------------------------------------------------------------------*/

char	*get_no_path(char *path)
{
	char	*slash;

	slash = ft_strrchr(path, '/');
	if (!slash)
		return (ft_strdup(path));
	return (ft_substr(path, slash - path + 1, ft_strlen(slash)));
}

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Get ONLY the ABSOLUTE base path of a file
| ----/ Params:	path
| ----/ Return:	New malloced string with the result
*----------------------------------------------------------------------------*/

char	*get_base_path(char *path)
{
	char	*slash;
	char	*base_path;
	char	*temp;

	if (!path)
		return (NULL);
	base_path = get_abs_path(path);
	slash = ft_strrchr(base_path, '/');
	if (slash)
	{
		temp = base_path;
		base_path = ft_substr(base_path, 0, slash - base_path);
		free(temp);
	}
	return (base_path);
}

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Get the ABSOLUTE base path of a file, file included
| ----/ Params:	path
| ----/ Return:	New malloced string with the result
*----------------------------------------------------------------------------*/

char	*get_abs_path(char *path)
{
	char	*abs_path;
	char	*slash;
	char	*current;
	char	*temp;

	if (!path)
		return (NULL);
	current = NULL;
	current = getwd(current);
	if (strstr(path, current))
		return (ft_strdup(path));
	if (current == NULL)
		return (NULL);
	slash = ft_strrchr(path, '/');
	if (slash)
		abs_path = ft_strjoin(current, path);
	else
	{
		temp = ft_strjoin(current, "/");
		abs_path = ft_strjoin(temp, path);
		free (temp);
	}
	free (current);
	return (abs_path);
}

/*----------------------------------------------------------------------------
| ----/ Bfrief:	Get the list of the directory
| ----/ Params:	path
| ----/ Return:	first element of linked list
*----------------------------------------------------------------------------*/

t_files	*list_dir_files(char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	t_files			*file_list;

	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	file_list = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (add_file_list(&file_list, ft_strdup(entry->d_name)))
			return (NULL);
		entry = readdir(dir);
	}
	closedir(dir);
	return (file_list);
}

bool	add_file_list(t_files **file_list, char	*file)
{
	t_files		*temp;
	t_files		*last;

	if (file[0] == '.' || (file[0] == '.' && file[0] == '.'))
		return (EXIT_SUCCESS);
	temp = ft_calloc(sizeof(t_files), 1);
	if (temp == NULL)
		return (EXIT_FAILURE);
	temp->file = file;
	if (*file_list)
	{
		last = *file_list;
		while (last->next)
			last = last->next;
		temp->prev = last;
		last->next = temp;
	}
	else
		(*file_list) = temp;
	return (EXIT_SUCCESS);
}
