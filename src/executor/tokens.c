#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

char	*ft_chrjoin(char	*str, char	c);

bool is_word_limit(char c)
{
	if (c == '&')
		return (true);
	if (c == '>')
		return (true);
	if (c == '<')
		return (true);
	if (c == ' ')
		return (true);
	if (c == '\0')
		return (true);
	return (false);
}

char	*get_word(char **data)
{
	char	*new_data;

	new_data = ft_strdup("");
	while (**data && !is_word_limit(**data))
		new_data = ft_chrjoin(new_data, *(*data)++);
	return (new_data);
}

char	**get_tokens(char *data, t_master *master)
{
	char	**tokens;
	int		num_tokens;
	char	*token;
	bool	is_quoted;
	bool	is_dbl_quoted;

	(void) master;
	tokens = malloc (sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	num_tokens = 0;	
	while (*data)
	{
		token = get_word(&data);
		num_tokens++;
		tokens = ft_realloc(tokens, num_tokens * sizeof(char *));	
		if (tokens == NULL)
			return (NULL);
		if (is_quoted)
			tokens[num_tokens] = token;
		else if(is_dbl_quoted)
		{
			// Expandimos entrecomiilado
		}
		else
		{
			// Expandimos todo
	
			if (*data == ' ')
				data++;
		}
		tokens[num_tokens] = token;
		if (*data == 39)
			is_quoted = !is_quoted;
		if (*data == 34)
			is_dbl_quoted = !is_dbl_quoted;
	}
	tokens = ft_realloc(tokens, num_tokens * sizeof(char *));
	tokens[num_tokens] = NULL;
	return (tokens);
}