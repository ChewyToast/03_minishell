/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:37 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/08 02:03:15 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "expander.h"
#include "defines.h"
#include "utils.h"
#include "env.h"

//	---- local headers
static	char *quotes_handler(t_tokener *tk, char	*new_data);
static	char *dolar_handler(t_tokener *tk, char *new_data);
static	char *scape_handler(t_tokener *tk, char *new_data);
static	char *tilde_handler(t_tokener *tk, char *new_data);
static	char *token_and_expand(char *data_in, t_master *master_in, int reset, bool no_wilcard);
char	*dolar_expansion(char **data, t_env *env_list);

//	---- public
char	*init_tokenizer(char *data_in, t_master *master, bool wildcard)
{
	return (token_and_expand(data_in, master, 1, wildcard));
}

char	*get_next_token(bool wildcard)
{
	return (token_and_expand(NULL, NULL, 0, wildcard));
}

/*
		1.- Preconditions
			Si no está escapado y el token es nuevo -> avanzamos los espacios
			Si ya estamos en la posición de fin de expanded_mode --> tk->exp_mode = 0
		3.- Si hay backslash, no esta entre comillas simples y no es modo expandido,
			Intentamos escaparlo
		4.- Revisamos si comienza o termina estado quoted o dbl_quoted. 
			Retornamos new_data igual que entro excepto si son dos comillas (dobles o simples)
			En este caso deberemos devolver un token vacio (no nulo)
		6.- Si encontramos dolar no escapado, expandimos la linea de comando
		7.- Si encontramos asterisco no escapado, expandimos la linea de comando
		8.- Si encontramos un espacio no escapado, generamos un nuevo token.
		9.- Si no ha ocurrido nada de lo anterior añadimos el caracter al token que 
			estamos construyendo
*/

//	---- private
static	char	*token_and_expand(char *data_in, t_master *master_in, int reset, bool wilcard)
{
	static t_tokener	tk;
	char				*new_data;

	new_data = tknexp_init(data_in, &tk, master_in, reset);
	while (*tk.data && new_data && !tk.return_token)
	{
		pre_conditions(&tk, new_data);
		if (*tk.data == 92 && ((!tk.is_quoted && !tk.exp_mode) || (tk.is_quoted_dolar && is_especial(tk.data))))
			new_data = scape_handler(&tk, new_data);
		else if (*tk.data == 39 || (*tk.data) == 34)
			new_data = quotes_handler(&tk, new_data);
		else if (*tk.data == '$' && !tk.is_quoted && !tk.exp_mode)
			new_data = dolar_handler(&tk, new_data);
		else if (*tk.data == '*' && !is_literal(&tk) && tk.exp_mode != 2 && wilcard)
			new_data = expand_wildcard(&tk, new_data);
		else if (*tk.data == '~' && !is_literal(&tk))
			new_data = tilde_handler (&tk, new_data);
		else if (*tk.data == ' ' && !is_literal(&tk) && tk.data++)
			return (new_data);
		else
			new_data = ft_chrjoin(new_data, *(tk.data++));
	}
	tk.return_token = 0;
	return (new_data);
}

static char	*quotes_handler(t_tokener *tk, char	*new_data)
{
	if ((*tk->data) == 39 && !tk->is_dbl_quoted && !tk->exp_mode)
	{
		if (quotes_sub_handler(tk, 39))
		{
			tk->return_token = true;
			return (ft_strdup(""));
		}
	}
	else if ((*tk->data) == 34 && !tk->is_quoted && !tk->exp_mode)
	{
		if (quotes_sub_handler(tk, 34))
		{
			tk->return_token = true;
			return (ft_strdup(""));
		}
	}
	else 
		new_data = ft_chrjoin(new_data, *(tk->data++));
	return (new_data);
}

static char	*dolar_handler(t_tokener *tk, char *new_data)
{
	char	*expanded;

	tk->data++;
	if ((*tk->data) == ' ' || (is_word_limit(*tk->data, LIM_DOLLAR) &&  (*tk->data) != '?') || (*tk->data) == 92)
	{
		if (*tk->data == '\'' || *tk->data == '\"')
		{
			if (*tk->data == '\'')
				tk->is_quoted_dolar = 1;
		}
		else
			new_data = ft_chrjoin(new_data, '$');
	}
	else
	{
		tk->data--;
		expanded = dolar_expansion(&tk->data, tk->master->env_list);
		tk->exp_mode = 1;
		tk->data = str_pro_join(tk->data, expanded, 0);
		tk->end_expansion = tk->data + ft_strlen(expanded);
		free(expanded);
		free(tk->original_promt);
		tk->original_promt = tk->data;
	}
	return (new_data);
}

char	*dolar_expansion(char **data, t_env *env_list)
{
	char	*expanded;
	int		pos;
	char	*word;
	char	*value;
	
	expanded = ft_strdup("");
	while (*data && **data == '$')
	{
		(*data)++;
		if (**data == '?')
		{
			expanded = ft_itoa(global.num_return_error);
			(*data)++;
		}
		else
		{
			pos = get_word_end(*data, LIM_DOLLAR) - *data;
			word = ft_substr(*data, 0, pos);
			value = env_get_value(env_list, word);
			free(word);
			if (value != NULL)
				expanded = ft_strjoin_free(expanded, value);
			*data += pos;
		}
	}
	return (expanded);
}

static char	*scape_handler(t_tokener *tk, char *new_data)
{
	char	to_scape;

	to_scape = *(tk->data + 1);
	// Si el siguiente caracter es NULL, avanzamos el dato sin escapar nada
	if (to_scape == '\0')
		tk->data++;
	// Cuando estamos entre comillas dobles NO se escapan los carcáteres 
	// excepto '\$' y '\\'
	else if (tk->is_dbl_quoted && to_scape && to_scape != 34 \
			&& to_scape != '$' && to_scape != 92)
		new_data = ft_chrjoin(new_data, *tk->data++);
	// Escapamos el caracter, añadimos el caracter despues de la contrabarra 
	// y nos posicionamos uno más allá.
	else
	{
		tk->data++;
		if (tk->is_quoted_dolar)
		{
			if (*(tk->data) == 't')
				new_data = ft_chrjoin(new_data, '\t');
			if (*(tk->data) == 'n')
				new_data = ft_chrjoin(new_data, '\n');
			if (*(tk->data) == 'v')
				new_data = ft_chrjoin(new_data, '\v');
			if (*(tk->data) == 'r')
				new_data = ft_chrjoin(new_data, '\r');
		}	
		else
			new_data = ft_chrjoin(new_data, *(tk->data));
		tk->data++;
	}
	return (new_data);
}

static char	*tilde_handler(t_tokener *tk, char *new_data)
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
	else if (post_tilde && pre_tilde == ' ')
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


