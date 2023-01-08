#include "structs.h"
#include "minishell.h"

bool match_wildcard(const char* s, const char* pattern) 
{
    while (*pattern) {
        if (*pattern == '*') {
            // Skip multiple consecutive wildcard characters
            while (*pattern == '*') {
                pattern++;
            }
            if (!*pattern) {
                // If the wildcard is the last character in the pattern, then it matches everything
                return true;
            }
            while (*s) {
                if (match_wildcard(s, pattern)) {
                    return (true);
                }
                s++;
            }
            return false;
        } else if (*pattern == '?') {
            // '?' matches any single character
            pattern++;
            s++;
        } else if (*pattern == *s) {
            // If the characters match, move to the next character in both strings
            pattern++;
            s++;
        } else {
            // If the characters don't match, then the pattern does not match the string
            return false;
        }
    }
    // If we reached the end of the pattern and the string, then the pattern matches the string
    return !*s;
}



int		num_new_args(char **command)
{
	return (1);
}

bool	is_expanded(char *arg)
{
	if (ft_strchr (arg, '*') || ft_strchr (arg, '?'))
		return (true);
	else
		return (false);
}

char	**expand_arg(char *arg)
{
	char	**expanded;

	return (expanded);
}

char	**expand_wildcard(char **command)
{
	char	**expanded;
	char	**expanded_arg;
	int		i;
	int		j;
	int		t;

	expanded = ft_calloc((num_new_args(command) + 1), sizeof(char*));
	expanded[0] = ft_strdup(command[0]);
	i = 0;
	j = 1;
	while (command[++i])
	{
		if (is_expanded(command[i]))
		{	
			t = 0;
			expanded_arg = expand_arg(command[i]);
			while (expanded_arg[t])
			{
				expanded[j] = expanded_arg[t];
				t++;
				j++;
			}
		}
		else
		{
			expanded[j] = ft_strdup(command[i]);
			j++;
		}
	}
	return (expanded);
}
