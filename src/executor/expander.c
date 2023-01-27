#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

bool 	is_word_limit(char c);
char	*get_word_end(char *data);
char	*get_word_init(char *data, char *data_min);
char	*ft_strjoin_free(char	*str1, char	*str2);
char	*ft_chrjoin(char	*str, char	c);
char	*get_redirect_end(char *data);
char	**expand_wildcard(char *token);
char	*check_quotes(char *data, bool *is_quoted, bool *is_dbl_quoted);

char	**expander(char *data, t_master *master)
{
	char	**tokens;
	char	*full_data;
	bool	is_quoted;
	bool	is_dbl_quoted;
	int		pos;
	char	*word;
	char	*expanded;

	full_data = data;
	tokens = malloc (sizeof (char *) * 2);
	tokens[0] = ft_strdup("");
	if (tokens == NULL)
		return (NULL);
	while (*data)
	{
		if (*(data) == 92 && !is_quoted)
		{
			tokens[0] = ft_chrjoin(tokens[0], *(++data));
			data++;
		}
		data = check_quotes(data, &is_quoted, &is_dbl_quoted);
		if ((*data) == '$' && !is_quoted)
		{
			data++;
			pos = get_word_end(data) - data;
			word = ft_substr(data, 0, pos);
			expanded = env_get_value(master->env_list, word);
			free (word);
			if (expanded != NULL)
				tokens[0] = ft_strjoin_free (tokens[0], expanded);
			data = data + pos;
		}
		else if ((*data) == '*' && !is_quoted)
		{
			data = get_word_init(data, full_data);
			word = ft_substr(data, 0, get_word_end(data) - data);
			free_split(tokens);
			free (full_data);
			return (expand_wildcard(word));
		}
		else if ((*data) == '~')
		{
			if (*(data - 1) == ' ')
			{
				expanded = env_get_value(master->env_list, "HOME");
				if (expanded == NULL)
					expanded = ft_strdup(master->tild_value);
				tokens[0] = ft_strjoin_free (tokens[0], expanded);
				data++;
			}
			else
				tokens[0] = ft_chrjoin(tokens[0], *(data++));
		}
		else
			tokens[0] = ft_chrjoin(tokens[0], *(data++));		
	}
	tokens[1] = NULL;
	free (full_data);
	return (tokens);	
}


// char	*expander(char *data, t_master *master)
// {
// 	char	*new_data;
// 	char	*expanded;
// 	char	*word;
// 	bool	is_quoted;
// 	bool	is_dbl_quoted;
// 	int		pos;
// 	char	*full_data;
// 	char	*word_init;
// 	int		to_delete;
// 	char	*temp;
// 	char	*redirect_data;
	
// 	(void)temp;
// 	(void)redirect_data;
// 	full_data = data;
// 	new_data = ft_strdup("");
// 	while (*data)
// 	{
// 		if (*(data) == 92 && !is_quoted)
// 		{
// 			new_data = ft_chrjoin(new_data, *(++data));
// 			data++;
// 		}
// 		if ((*data) == 39)
// 		{
// 			is_quoted = !is_quoted;
// 			data++;
// 		}
// 		else if ((*data) == 34)
// 		{
// 			is_dbl_quoted = !is_dbl_quoted;
// 			data++;
// 		}
// 		else if (!is_quoted && !is_dbl_quoted && *data == ' ' && (*(data + 1) == ' ' || *(data + 1) == '\0'))
// 			data++;
// 		else if (*data == ' ' && (*(data + 1) == '>' || *(data + 1) == '<') && !is_quoted && !is_dbl_quoted)
// 			data++;
// 		// else if (((*data) == '>' || (*data) == '<') && !is_quoted && !is_dbl_quoted)
// 		// {
// 		// 	data++;
// 		// 	while (*(data) == ' ' && *(data - 1) != 39 && *(data - 1) != 34)
// 		// 		data++;
// 		// 	pos = get_redirect_end(data) - (data);
// 		// 	word = ft_substr(data, 0, pos - 1);
// 		// 	word = expand_data(word, node, master);
// 		// 	add_new_redirect(node, word, *data);
// 		// 	data = data + pos;
// 		// }	
// 		else if ((*data) == '$' && !is_quoted)
// 		{
// 			data++;
// 			pos = get_word_end(data) - data;
// 			word = ft_substr(data, 0, pos);
// 			expanded = env_get_value(master->env_list, word);
// 			free (word);
// 			if (expanded != NULL)
// 				new_data = ft_strjoin_free (new_data, expanded);
// 			data = data + pos;
// 		}		
// 		else if ((*data) == '*' && !is_quoted)
// 		{
// 			word_init = get_word_init(data, full_data);
// 			to_delete = data - word_init;
// 			temp = ft_substr(new_data, 0, ft_strlen(new_data) - to_delete);
// 			free (new_data);
// 			new_data = temp;
// 			data = get_word_init(data, full_data);
// 			pos = get_word_end(data) - data;
// 			word = ft_substr(data, 0, pos);
// 			expanded = expand_str_wildcard(word);
// 			new_data = ft_strjoin_free (new_data, expanded);
// 			data = data + pos;
// 		}
// 		else if ((*data) == '~')
// 		{
// 			if (*(data - 1) == ' ')
// 			{
// 				expanded = env_get_value(master->env_list, "HOME");
// 				if (expanded == NULL)
// 					expanded = ft_strdup(master->tild_value);
// 				new_data = ft_strjoin_free (new_data, expanded);
// 				data++;
// 			}
// 			else
// 				new_data = ft_chrjoin(new_data, *(data++));
// 		}
// 		else
// 			new_data = ft_chrjoin(new_data, *(data++));
// 	}
// 	free (full_data);
// 	return (new_data);
// }

// char	**get_tokens(char *data)
// {
// 	char **tokens;
// 	char *last_token;
// 	char *token;
// 	int	num_tokens;
	
// 	tokens = malloc (sizeof (char *));
// 	if (tokens == NULL)
// 		return (NULL);
// 	last_token = data;
// 	num_tokens = 0;
// 	while(*data)
// 	{
// 		if ((*data == ' '  &&  *(data - 1) != ' ') || *(data + 1) == '\0')
// 		{
// 			if (*(data + 1) == '\0')
// 				data++;
// 			token = ft_substr(last_token, 0, data - last_token);
// 			if (num_tokens == 0)
// 				token = ft_substr(token, 0, ft_strchr(token, ' ') - token);
// 			num_tokens++;
// 			tokens = ft_realloc(tokens, sizeof (char *) * (num_tokens + 1));
// 			if (tokens == NULL)
// 				return (NULL);
// 			tokens[num_tokens - 1] = token;
// 			last_token = data + 1;
// 		}
// 		if (*(data) == '\0')
// 			break;
// 		data++;
// 	}
// 	tokens[num_tokens] = NULL;
// 	return (tokens);
// }


bool is_word_limit(char c)
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
