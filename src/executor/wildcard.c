#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

bool	match_wildcard(const char* s, const char* pattern);
char	**expand_arg(char *arg);
bool	is_expanded(char *arg);

char	**expand_wildcard(char **command)
{
	char	**expanded;
	char	**expanded_arg;
	int		i;
	int		j;
	int		t;

	expanded = ft_calloc(sizeof(char*), 1);
	if (!expanded)
		return (NULL);
	expanded[0] = ft_strdup(command[0]);
	i = 0;
	j = 1;
	while (command[++i])
	{
		if (is_expanded(command[i]))
		{	
			t = 0;
			expanded_arg = expand_arg(command[i]);
			if (!expanded_arg)
				return (NULL);
			while (expanded_arg[t])
			{
				expanded = ft_realloc(expanded, (j + 2) * sizeof(char *));
				if (!expanded)
					return (NULL);
				expanded[j] = expanded_arg[t];
				t++;
				j++;
			}
			free(expanded_arg);
		}
		else
		{
			expanded = ft_realloc(expanded, (j + 2) * sizeof(char *));
			if (!expanded)
				return (NULL);
			expanded[j] = ft_strdup(command[i]);
			j++;
		}
	}
	expanded[j] = NULL;
	free_split(command);
	return (expanded);
}

char	**expand_arg(char *arg)
{
	char	**expanded;
	char	*to_expand;
	char	*base_path;
	int		num_files;
	t_files	*files;
	t_files	*temp;

	to_expand = get_no_path(arg);
	base_path = get_base_path(arg);
	files = list_dir_files(base_path);
	free (base_path);
	if (!files)
		return (NULL);
	num_files = 0;
	expanded = ft_calloc(sizeof(char*), 1);
	if (!expanded)
		return (NULL);
	while (files)
	{
		if (match_wildcard(files->file, to_expand))
		{
			expanded = ft_realloc(expanded, (num_files + 2) * sizeof(char *));
			if (!expanded)
				return (NULL);
			expanded[num_files] = ft_strdup(files->file);
			num_files++;
		}
		free(files->file);
		temp = files;
		files = files->next;
		free(temp);
	}
	free (to_expand);
	expanded[num_files] = NULL;
	return (expanded);
}

bool match_wildcard(const char* s, const char* pattern) 
{
	while (*pattern) 
	{
		if (*pattern == '*') 
		{
			// Skip multiple consecutive wildcard characters
			while (*pattern == '*') 
				pattern++;
			 // If the wildcard is the last character in the pattern, then it matches everything	
			 if (!*pattern) 
				return true;
			while (*s) 
			{
				if (match_wildcard(s, pattern))
					return (true);
				s++;
			}
			return false;
		} 
		// '?' matches any single character
		else if (*pattern == '?') 
		{
			pattern++;
			s++;
		}
		// If the characters match, move to the next character in both strings
		else if (*pattern == *s) 
		{
			pattern++;
			s++;
		} 
		// If the characters don't match, then the pattern does not match the string
		else 
			return false;
	}
	// If we reached the end of the pattern and the string, then the pattern matches the string
	return !*s;
}

bool	is_expanded(char *arg)
{
	if (ft_strchr (arg, '*') || ft_strchr (arg, '?'))
		return (true);
	else
		return (false);
}
