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
char	*scape_handler(char **in_data, char *new_data, bool is_dbl_quoted);
char	*parse_token(char *data_in, t_master *master_in, int reset);
char	*get_recursive_expands(char **str_base, t_master *master);
int		is_isolated_quotes(char	*data, char quote);

#define LIM_DOLLAR 1
#define LIM_WILDCARD 2
#define LIM_INIT 3


char	*init_tokenizer(char *data_in, t_master *master)
{
	return(parse_token(data_in, master, 1));
}

char	*get_next_token()
{
	return(parse_token(NULL, NULL, 0));
}

char	*parse_token(char *data_in, t_master *master_in, int reset)
{

	static char		*data;
	static char		*end_expansion;
	static t_master *master;
	static bool		is_quoted;
	static bool 	is_dbl_quoted;
	static int		is_expanded_mode;
	static char		*original_promt;

	int		pos;
	char	*new_data;
	char	*expanded;
	char	*word;
	char	*full_data;
	char 	*word_init;
	int 	to_delete;
	char 	*temp;
	char	*value;
	

	if (reset && !data_in)
		return (NULL);
	if (reset)
	{
		if (original_promt)
			free(original_promt);
		data = ft_strdup(data_in);
		original_promt = data;
		master = master_in;
		is_quoted = 0;
		is_dbl_quoted = 0;
		is_expanded_mode = 0;
		end_expansion = NULL;
	}
	full_data = data;
	new_data = ft_strdup("");
	spaces_clean(&data);
	if(!*data)
		return (NULL);
	while (*data)
	{
		// Si no está escapado y el token es nuevo -> avanzamos los espacios
		if (!is_quoted && !is_dbl_quoted && ft_strlen (new_data) == 0)
			spaces_clean(&data);
		// Revisamos si ya no estamos en modo expandido
		if (is_expanded_mode && data >= end_expansion)
			is_expanded_mode = 0;
		// Si hay backslash y no esta entre comillas simpoles y no es modo expandido, intentamos escaparlo
		if (*(data) == 92 && !is_quoted && !is_expanded_mode)
		{
			// Si el siguiente caracter es NULL, avanzamos el dato sin escapar nada
			if (*(data + 1) == '\0')
				data++;
			// Cuando estamos entre comillas dobles NO se escapan los carcáteres excepto '\$' y '\\'
			else if (is_dbl_quoted && *(data + 1) && (*(data + 1) != 34 && *(data + 1) != '$' && *(data + 1) != 92))
				new_data = ft_chrjoin(new_data, *(data++));
			else
			{
				// Escapamos el caracter, añadimos el caracter despues de la contrabarra y nos posicionamos uno más allá.
				new_data = ft_chrjoin(new_data, *(++data));
				data++;
			}
		}
		// Comilla simple, solo mantiene su funcion especial si:
		//		No esté entre comilla doble
		//		No está dentro de una expansión
		else if ((*data) == 39 && !is_dbl_quoted && !is_expanded_mode)
		{
			is_quoted = !is_quoted;
			if (is_isolated_quotes(data, 39))
			{
				is_quoted = !is_quoted;
				while (*data == 39)
					data++;
				if (*data)
					data++;
				return(ft_strdup(""));
			}
			data++;
		}
		// Comilla doble, solo mantiene su funcion especial si:
		//		No esté entre comilla simple
		//		No está dentro de una expansión
		else if ((*data) == 34 && !is_quoted && !is_expanded_mode)
		{
			is_dbl_quoted = !is_dbl_quoted;
			if (is_isolated_quotes(data, 34))
			{
				is_dbl_quoted = !is_dbl_quoted;
				while (*data == 34)
					data++;
				if (*data)
					data++;
				return(ft_strdup(""));
			}
			data++;
		}
		// Si encontramos dolar no escapado, expandimos la linea de comando
		else if ((*data) == '$' && !is_quoted && !is_expanded_mode)
		{
			data++;
			if ((*data) == ' ' || (*data) == 92 || (*data) == '\0')
				new_data = ft_chrjoin(new_data, '$');
			else
			{
				data--;
				expanded = ft_strdup("");
				while (*data == '$')
				{
					data++;
					pos = get_word_end(data, LIM_DOLLAR) - data;
					word = ft_substr(data, 0, pos);
					value = env_get_value(master->env_list, word);
					if (value !=NULL)
						expanded = ft_strjoin_free(expanded, value);
					data += pos;
				}
				is_expanded_mode = 1;
				data = str_pro_join(data, expanded, 0);
				end_expansion = data + ft_strlen(expanded);
				free (word);
			}
		}
		// Si encontramos asterisco no escapado, expandimos la linea de comando
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
		// Si encontramos una tilde no escapadala expandimos
		else if ((*data) == '~' && !is_quoted && !is_dbl_quoted )
		{
			expanded = expand_tide(&data, master);
			new_data = ft_strjoin_free(new_data, expanded);
		}
		// Si encontramos un espacio no escapado, generamos un nuevo token.
		else if (*data == ' ' && !is_quoted && !is_dbl_quoted)
		{
			data++;
			return (new_data);
		}
		// Si no ha ocurrido nada de lo anterior añadimos el caracter al token que estamos construyendo
		else
			new_data = ft_chrjoin(new_data, *(data++));
	}
	// Si termoina la cadena de origen, devolvemos el token
	return (new_data);
}

char	*str_pro_join(char *str1, char *str2, int pos)
{
	int		new_size;
	char	*new_str;
	char	*ret_str;

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

int		is_isolated_quotes(char	*data, char quote)
{

	if (!ft_isspace(*(data - 1)))
		return (false);
	if (*(data + 1) != quote)
		return (false);
	if (*(data + 2) == '\0')
		return (true);
	if (!ft_isspace(*(data + 2)))
		return (false);
	return (true);
}

char	*scape_handler(char **data, char *new_data, bool is_dbl_quoted)
{
	if (*(*data + 1) == '\0')
		(*data)++;
	else if (is_dbl_quoted && *(*data + 1) && (*(*data + 1) != 34 && *(*data + 1) != '$' && *(*data + 1) != 92))
		new_data = ft_chrjoin(new_data, *((*data)++));
	else
	{
		new_data = ft_chrjoin(new_data, *(++(*data)));
		(*data)++;
	}
	return (new_data);
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
		if (!ft_isalnum(c) && c != '_')
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
	while (*data && !is_word_limit(*data, type) && data >= data_min)
		data--;
	return (++data);
}
