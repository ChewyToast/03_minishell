#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>


typedef struct s_tokener 	t_tokener;

struct s_tokener
{
	char		*data;
	char		*end_expansion;
	t_master 	*master;
	bool		is_quoted;
	bool 		is_dbl_quoted;
	int			is_expanded_mode;
	char		*original_promt;
	char		*full_data;
};


bool	is_word_limit(char c,  int type);
char	*get_word_end(char *data, int type);
char	*get_word_init(char *data, char *data_min, int type);
char	*ft_strjoin_free(char *str1, char *str2);
char	*ft_chrjoin(char *str, char c);
char	*get_redirect_end(char *data);
char	*check_quotes(char *data, bool *is_quoted, bool *is_dbl_quoted);
char	*expand_tide(char **data, t_master *master);
char	*str_pro_join(char *str1, char *str2, int pos);
char	*scape_handler(t_tokener *tk, char *new_data);
char	*parse_token(char *data_in, t_master *master_in, int reset);
int		is_isolated_quotes(char	*data, char quote);
int		quotes_handler(t_tokener *tk, char type);
char	*expand_wildcard(t_tokener *tk, char *new_data);
char	*tilde_handler (t_tokener *tk, char *new_data);
char 	*dolar_handler(t_tokener *tk, char *new_data);

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
	static t_tokener		tk;
	char	*new_data;
	
	if (reset && !data_in)
		return (NULL);
	if (reset)
	{
		if (tk.original_promt)
			free(tk.original_promt);
		tk.data = ft_strdup(data_in);
		tk.original_promt = tk.data;
		tk.master = master_in;
		tk.is_quoted = 0;
		tk.is_dbl_quoted = 0;
		tk.is_expanded_mode = 0;
		tk.end_expansion = NULL;
	}
	tk.full_data = tk.data;
	new_data = ft_strdup("");
	spaces_clean(&tk.data);
	if(!*tk.data)
		return (NULL);
	while (*tk.data)
	{
		// Si no está escapado y el token es nuevo -> avanzamos los espacios
		if (!tk.is_quoted && !tk.is_dbl_quoted && ft_strlen (new_data) == 0)
			spaces_clean(&tk.data);
		// Revisamos si ya no estamos en modo expandido
		if (tk.is_expanded_mode && tk.data >= tk.end_expansion)
			tk.is_expanded_mode = 0;
		// Si hay backslash y no esta entre comillas simpoles y no es modo expandido, intentamos escaparlo
		if (*(tk.data) == 92 && !tk.is_quoted && !tk.is_expanded_mode)
			new_data = scape_handler(&tk, new_data);
		// Comilla simple, solo mantiene su funcion especial si:
		//		No esté entre comilla doble
		//		No está dentro de una expansión
		else if ((*tk.data) == 39 && !tk.is_dbl_quoted && !tk.is_expanded_mode)
		{
			if (quotes_handler(&tk, 39))
				return (ft_strdup(""));
		}
		// Comilla doble, solo mantiene su funcion especial si:
		//		No esté entre comilla simple
		//		No está dentro de una expansión
		else if ((*tk.data) == 34 && !tk.is_quoted && !tk.is_expanded_mode)
		{
			if (quotes_handler(&tk, 34))
				return (ft_strdup(""));
		}
		// Si encontramos dolar no escapado, expandimos la linea de comando
		else if ((*tk.data) == '$' && !tk.is_quoted && !tk.is_expanded_mode)
			new_data = dolar_handler(&tk, new_data);
		// Si encontramos asterisco no escapado, expandimos la linea de comando
		else if ((*tk.data) == '*' && !tk.is_quoted && !tk.is_dbl_quoted && tk.is_expanded_mode != 2)
			new_data = expand_wildcard(&tk, new_data);
		else if ((*tk.data) == '~' && !tk.is_quoted && !tk.is_dbl_quoted )
			new_data = tilde_handler (&tk, new_data);
		// Si encontramos un espacio no escapado, generamos un nuevo token.
		else if (*tk.data == ' ' && !tk.is_quoted && !tk.is_dbl_quoted && tk.data++)
			return (new_data);
		// Si no ha ocurrido nada de lo anterior añadimos el caracter al token que estamos construyendo
		else
			new_data = ft_chrjoin(new_data, *(tk.data++));
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

int	quotes_handler(t_tokener *tk, char type)
{
	if (type == 39)
		tk->is_quoted = !tk->is_quoted;
	if (type == 34)
		tk->is_dbl_quoted = !tk->is_dbl_quoted;
	if ((type == 39 && !tk->is_quoted) || (type == 34 && !tk->is_dbl_quoted))
	{
		tk->data++;
		return (0);
	}
	if (is_isolated_quotes(tk->data, type))
	{
		if (type == 39)
			tk->is_quoted = !tk->is_quoted;
		if (type == 34)
			tk->is_dbl_quoted = !tk->is_dbl_quoted;
		while (*tk->data == type)
			tk->data++;
		if (*tk->data)
			tk->data++;
		return (1);
	}
	tk->data++;
	return (0);
}

char *dolar_handler(t_tokener *tk, char *new_data)
{
	int		pos;
	char	*expanded;
	char	*word;
	char	*value;

	tk->data++;
	if ((*tk->data) == ' ' || (*tk->data) == 92 || (*tk->data) == '\0')
		new_data = ft_chrjoin(new_data, '$');
	else
	{
		tk->data--;
		expanded = ft_strdup("");
		while (*tk->data == '$')
		{
			tk->data++;
			pos = get_word_end(tk->data, LIM_DOLLAR) - tk->data;
			word = ft_substr(tk->data, 0, pos);
			value = env_get_value(tk->master->env_list, word);
			if (value != NULL)
				expanded = ft_strjoin_free(expanded, value);
			tk->data += pos;
		}
		tk->is_expanded_mode = 1;
		tk->data = str_pro_join(tk->data, expanded, 0);
		tk->end_expansion = tk->data + ft_strlen(expanded);
		free(word);
	}
	return (new_data);
}


char	*scape_handler(t_tokener *tk, char *new_data)
{
	char	to_scape;

	to_scape = *(tk->data + 1);
	// Si el siguiente caracter es NULL, avanzamos el dato sin escapar nada
	if (to_scape == '\0')
		tk->data++;
	// Cuando estamos entre comillas dobles NO se escapan los carcáteres excepto '\$' y '\\'
	else if (tk->is_dbl_quoted && to_scape && to_scape != 34 && to_scape != '$' && to_scape != 92)
		new_data = ft_chrjoin(new_data, (*tk->data)++);
	// Escapamos el caracter, añadimos el caracter despues de la contrabarra y nos posicionamos uno más allá.
	else
	{
		new_data = ft_chrjoin(new_data, *(++tk->data));
		tk->data++;
	}
	return (new_data);
}

char	*expand_wildcard(t_tokener *tk, char *new_data)
{
	int		pos;
	char	*expanded;
	char	*word;
	char 	*word_init;
	int 	to_delete;
	char 	*temp;

	word_init = get_word_init(tk->data, tk->full_data, LIM_INIT);
	to_delete = tk->data - word_init;
	temp = ft_substr(new_data, 0, ft_strlen(new_data) - to_delete);
	free(new_data);
	new_data = temp;
	tk->data = get_word_init(tk->data, tk->full_data, 0);
	pos = get_word_end(tk->data, LIM_WILDCARD) - tk->data;
	word = ft_substr(tk->data, 0, pos);
	expanded = expand_str_wildcard(word);
	tk->data = str_pro_join(tk->data + pos, expanded, 0);
	tk->is_expanded_mode = 2;
	tk->end_expansion = tk->data + ft_strlen(expanded);
	return (new_data);
}

char	*tilde_handler (t_tokener *tk, char *new_data)
{
	int		pos;
	char	*expanded;
	char	*home_path;
	char	*new_str;
	char	pre_tilde;
	char	post_tilde;

	post_tilde = *(tk->data + 1);
	pre_tilde = *(tk->data - 1);
	new_str = ft_strdup("");
	if (pre_tilde == ' ' && (post_tilde == ' ' || post_tilde == '\0'))
	{
		home_path = env_get_value(tk->master->env_list, "HOME");
		if (home_path == NULL)
			home_path = ft_strdup(tk->master->tild_value);
		new_str = ft_strjoin_free(new_str, home_path);
		(tk->data)++;
	}
	else if (post_tilde && pre_tilde  == ' ')
	{
		expanded = ft_substr(tk->data, 1, ft_strlen(tk->data) - 1);
		expanded = ft_strjoin_free(ft_strdup("/Users/"), expanded);
		if (access(expanded, F_OK))
			new_str = ft_chrjoin(new_str, *(tk->data++));
		else
		{
			new_str = ft_strjoin_free(new_str, expanded);
			pos = get_word_end(tk->data, LIM_DOLLAR) - tk->data;
			tk->data = tk->data + pos;
		}
	}
	else
	{
		new_str = ft_chrjoin(new_str, *tk->data);
		tk->data++;
	}
	return (ft_strjoin_free(new_data, new_str));
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
