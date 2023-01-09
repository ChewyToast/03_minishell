#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <dirent.h>


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
	char *abs_path;
	char *slash;
	char *current;
	char *temp;

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
	t_files			*temp;
	t_files			*last;

	dir = opendir(path);
	if (dir == NULL)
		return NULL;
	file_list = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		temp = ft_calloc(sizeof(t_files), 1);
		if (temp == NULL)
			return (NULL);
		temp->file = ft_strdup(entry->d_name);
		if (file_list)
		{
			temp->prev = last;
			last->next = temp;
			last = last->next;
		}
		else
		{
			file_list = temp;
			last = file_list;
		}
	}
	closedir(dir);
	return (file_list);
}