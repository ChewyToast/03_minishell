#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

bool	is_word_limit(char c);
char	*get_word_end(char *data);
char	*get_word_init(char *data, char *data_min);
char	*ft_strjoin_free(char *str1, char *str2);
char	*ft_chrjoin(char *str, char c);
char	*get_redirect_end(char *data);
char	**expand_wildcard(char *token);
char	*check_quotes(char *data, bool *is_quoted, bool *is_dbl_quoted);
char	*expand_tide(char **data, t_master *master);

char	*expander(char *data, t_master *master)
{
	char	*full_data;
	bool	is_quoted;
	bool	is_dbl_quoted;
	int		pos;
	char	*word;
	char	*expanded;
	char	*new_string;

	if (!data)
		return (NULL);
	full_data = data;
	new_string = ft_strdup("");
	if (new_string == NULL)
		return (NULL);
	while (*data)
	{
		// if (*(data) == 92 && !is_quoted)
		// {
		// 	new_string = ft_chrjoin(new_string, *(++data));
		// 	data++;
		// }
		check_quotes(data, &is_quoted, &is_dbl_quoted);
		if ((*data) == '$' && !is_quoted)
		{
			data++;
			pos = get_word_end(data) - data;
			word = ft_substr(data, 0, pos);
			expanded = env_get_value(master->env_list, word);
			free(word);
			if (expanded != NULL)
				new_string = ft_strjoin_free(new_string, expanded);
			data = data + pos;
		}
		else if ((*data) == '*' && !is_quoted && !is_dbl_quoted)
		{
			data = get_word_init(data, full_data);
			word = ft_substr(data, 0, get_word_end(data) - data);
			new_string = ft_strjoin_free(new_string, expand_str_wildcard(word));
		}
		else if ((*data) == '~' && !is_quoted && !is_dbl_quoted)
		{
			expanded = expand_tide(&data, master);
			new_string = ft_strjoin_free(new_string, expanded);
		}
		else
			new_string = ft_chrjoin(new_string, *(data++));
	}
	free(full_data);
	return (new_string);
}


char	*expand_tide(char **data, t_master *master)
{
	int		pos;
	char	*expanded;
	char	*home_path;
	char	*new_str;

	new_str = ft_strdup("");
	if (*((*data) - 1) == ' ' && (*((*data) - 1) == ' ' || *((*data) - 1) == '\0'))
	{
		home_path = env_get_value(master->env_list, "HOME");
		if (home_path == NULL)
			home_path = ft_strdup(master->tild_value);
		new_str = ft_strjoin_free(new_str, home_path);
		(*data)++;
	}
	else if (*(data + 1) && **(data + 1))
	{
		expanded = ft_substr(*data, 1, ft_strlen(*data) - 1);
		expanded = ft_strjoin_free(ft_strdup("/Users/"), expanded);
		if (access(expanded, F_OK))
			new_str = ft_chrjoin(new_str, *((*data)++));
		else
		{
			new_str = ft_strjoin_free(new_str, expanded);
			pos = get_word_end(*data) - *data;
			*data = *data + pos;
		}
	}
	else
		new_str = ft_chrjoin(new_str, **(data++));
	return (new_str);
}

bool	is_word_limit(char c)
{
	if (c == '>')
		return (true);
	if (c == '<')
		return (true);
	if (c == ' ')
		return (true);
	if (c == '.')
		return (true);
	if (c == '/')
		return (true);
	if (c == '$')
		return (true);
	if (c == 39)
		return (true);
	if (c == 34)
		return (true);
	if (c == '\0')
		return (true);
	return (false);
}

char	*get_word_end(char *data)
{
	while (*data && !is_word_limit(*data))
		data++;
	return (data);
}

char	*get_word_init(char *data, char *data_min)
{
	while (*data && !is_word_limit(*data) && data > data_min)
		data--;
	return (data);
}
