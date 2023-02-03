#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

bool	is_word_limit(char c,  int type);
char	*get_word_end(char *data, int type);
char	*get_word_init(char *data, char *data_min, int type);
char	*ft_strjoin_free(char *str1, char *str2);
char	*ft_chrjoin(char *str, char c);
char	*get_redirect_end(char *data);
char	*check_quotes(char *data, bool *is_quoted, bool *is_dbl_quoted);
char	*expand_tide(char **data, t_master *master);
char	*str_pro_join(char *str1, char *str2, int pos);

#define LIM_DOLLAR 1
#define LIM_WILDCARD 2
#define LIM_INIT 3

char	*parse_token(char *data_in, t_master *master, int reset)
{

	static char	*data;
	static bool	is_quoted;
	static bool is_dbl_quoted;
	static int	is_expanded_mode;

	int		pos;
	char	*new_data;
	char	*expanded;
	char	*word;
	char	*full_data;
	char	*end_expansion;
	char 	*word_init;
	int 	to_delete;
	char 	*temp;

	if (reset || !data)
	{
		data = data_in;
		is_quoted = 0;
		is_dbl_quoted = 0;
		is_expanded_mode = 0;
	}
	full_data = data;
	new_data = ft_strdup("");
	spaces_clean(&data);
	if(!*data)
		return (NULL);
	while (*data)
	{
		if (*(data) == 92 && !is_quoted && !is_dbl_quoted)
		{
			new_data = ft_chrjoin(new_data, *(++data));
			data++;
		}
		else if ((*data) == 39 && !is_dbl_quoted && !is_expanded_mode)
		{
			is_quoted = !is_quoted;
			data++;
		}
		else if ((*data) == 34 && !is_quoted && !is_expanded_mode)
		{
			is_dbl_quoted = !is_dbl_quoted;
			data++;
		}
		else if ((*data) == '$' && !is_quoted && !is_expanded_mode)
		{
			data++;
			if ((*data) == ' ' || (*data) == 92 || (*data) == '\0')
				new_data = ft_chrjoin(new_data, '$');
			else
			{
				pos = get_word_end(data, LIM_DOLLAR) - data;
				word = ft_substr(data, 0, pos);
				expanded = env_get_value(master->env_list, word);
				if (expanded != NULL)
				{
					data = str_pro_join(data + pos, expanded, 0);
					is_expanded_mode = 1;
					end_expansion = data + ft_strlen(expanded);	
				}
				else
					data += pos;
				if (!is_dbl_quoted)
					spaces_clean(&data);
				free (word);
			}
		}		
		else if ((*data) == '*' && !is_quoted && !is_dbl_quoted && is_expanded_mode != 2)
		{
			word_init = get_word_init(data, full_data, LIM_INIT);
			to_delete = data - word_init;
			temp = ft_substr(new_data, 0, ft_strlen(new_data) - to_delete);
			free (new_data);
			new_data = temp;
			data = get_word_init(data, full_data, 0);
			pos = get_word_end(data, LIM_WILDCARD) - data;
			word = ft_substr(data, 0, pos);
			expanded = expand_str_wildcard(word);
			data = str_pro_join(data + pos, expanded, 0);
			is_expanded_mode = 2;
				end_expansion = data + ft_strlen(expanded);
		}
		else if ((*data) == '~')
		{
			expanded = expand_tide(&data, master);
			new_data = ft_strjoin_free(new_data, expanded);
		}
		else if (!is_quoted && !is_dbl_quoted && *data == ' ')
			return (new_data);
		else
			new_data = ft_chrjoin(new_data, *(data++));
		if (data == end_expansion)
			is_expanded_mode = 0;
	}
	return (new_data);
}

char	*str_pro_join(char *str1, char *str2, int pos)
{
	int		new_size;
	char	*new_str;
	char	*ret_str;
	char	*str_free[2];

	str_free[0] = str1;
	str_free[1] = str2;
	new_size = ft_strlen(str1) + ft_strlen(str2);
	new_str = malloc (sizeof (char) * (new_size + 1));
	if (new_str == NULL)
		return (NULL);
	ret_str = new_str;
	while(*str1 && pos && pos--)
		*(new_str++) = *(str1++);
	while (*str2)
		*(new_str++) = *(str2++);
	while(*str1)
		*(new_str++) = *(str1++);
	*new_str = '\0';
	return (ret_str);
}


char	*expand_tide(char **data, t_master *master)
{
	int		pos;
	char	*expanded;
	char	*home_path;
	char	*new_str;

	new_str = ft_strdup("");
	if (*((*data) - 1) == ' ' && (*((*data) + 1) == ' ' || *((*data) + 1) == '\0'))
	{
		home_path = env_get_value(master->env_list, "HOME");
		if (home_path == NULL)
			home_path = ft_strdup(master->tild_value);
		new_str = ft_strjoin_free(new_str, home_path);
		(*data)++;
	}
	else if (*(data + 1) && *((*data) + 1)  && *(data - 1) && *((*data) - 1)  == ' ')
	{
		expanded = ft_substr(*data, 1, ft_strlen(*data) - 1);
		expanded = ft_strjoin_free(ft_strdup("/Users/"), expanded);
		if (access(expanded, F_OK))
			new_str = ft_chrjoin(new_str, *((*data)++));
		else
		{
			new_str = ft_strjoin_free(new_str, expanded);
			pos = get_word_end(*data, '.') - *data;
			*data = *data + pos;
		}
	}
	else
	{
		new_str = ft_chrjoin(new_str, **data);
		*data = *data + 1;
	}
	return (new_str);
}

bool	is_word_limit(char c, int type)
{
	if (type == LIM_DOLLAR)
	{
		if (!ft_isalnum(c))
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

	if (type == LIM_WILDCARD)
	{

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
	if (type == LIM_INIT)
	{
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
	return (false);
}

char	*get_word_end(char *data, int type)
{
	while (*data && !is_word_limit(*data, type))
		data++;
	return (data);
}

char	*get_word_init(char *data, char *data_min, int type)
{
	while (*data && !is_word_limit(*data, type) && data > data_min)
		data--;
	return (++data);
}
