/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:37 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/03 19:53:23 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "defines.h"
#include "utils.h"
#include "env.h"

//	---- local headers
static char	*quotes_handler(t_tokener *tk, char	*new_data);
static char	*dolar_handler(t_tokener *tk, char *new_data);
static char	*scape_handler(t_tokener *tk, char *new_data);
static char	*tilde_handler(t_tokener *tk, char *new_data);
static char	*token_and_expand(char *data_in, t_master *master_in, int reset,
				bool no_wilcard);
char		*dolar_expansion(char **data, t_env *env_list, char *expanded);
static bool	expander(char	**new_data, t_tokener *tk, bool wilcard);
static void	get_expanded_dollar(t_tokener *tk);
static char	*expand_tilde(t_tokener *tk, char *new_str);
static char	*expand_tilde_home(t_tokener *tk, char *new_str);

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
			Si no está escapado y el token es nuevo -> avanzamos los 
			espacios
			Si ya estamos en la posición
			de fin de expanded_mode --> tk->exp_mode = 0
		3.- Si hay backslash, no esta entre comillas simples y no es 
			modo expandido, Intentamos escaparlo
		4.- Revisamos si comienza o termina estado quoted o dbl_quoted. 
			Retornamos new_data igual que entro excepto si son dos 
			comillas (dobles o simples)
			En este caso deberemos devolver un token vacio (no nulo)
		6.- Si encontramos dolar no escapado, expandimos la linea de comando
		7.- Si encontramos asterisco no escapado, expandimos la linea de comando
		8.- Si encontramos un espacio no escapado, generamos un nuevo token.
		9.- Si no ha ocurrido nada de lo anterior añadimos el caracter al token que 
			estamos construyendo
*/

//	---- private
static	char	*token_and_expand(char *data_in, t_master *master_in, int reset,
					bool wilcard)
{
	static t_tokener	tk;
	char				*new_data;

	new_data = tknexp_init(data_in, &tk, master_in, reset);
	if (*tk.data == '\0')
		return (NULL);
	while (*tk.data && new_data && !tk.return_token)
	{
		pre_conditions(&tk, new_data);
		if (expander(&new_data, &tk, wilcard))
			return (new_data);
	}
	if (new_data[0] == '\0' && tk.full_data[0] == '$')
		return (NULL);
	tk.return_token = 0;
	return (new_data);
}

static bool	expander(char	**new_data, t_tokener *tk, bool wilcard)
{
	if (*tk->data == 92 && ((!tk->is_quoted && !tk->exp_mode)
			|| (tk->is_quoted_dolar && is_especial(tk->data))))
		*new_data = scape_handler(tk, *new_data);
	else if (*tk->data == 39 || (*tk->data) == 34)
		*new_data = quotes_handler(tk, *new_data);
	else if (*tk->data == '$' && !tk->is_quoted && !tk->exp_mode)
		*new_data = dolar_handler(tk, *new_data);
	else if (*tk->data == '*' && !is_literal(tk)
		&& tk->exp_mode != 2 && wilcard)
		*new_data = expand_wildcard(tk, *new_data);
	else if (*tk->data == '~' && !is_literal(tk))
		*new_data = tilde_handler (tk, *new_data);
	else if (*tk->data == ' ' && !is_literal(tk) && tk->data++)
		return (true);
	else
		*new_data = ft_chrjoin(*new_data, *(tk->data++));
	return (false);
}

static char	*quotes_handler(t_tokener *tk, char	*new_data)
{
	if ((*tk->data) == 39 && !tk->is_dbl_quoted && !tk->exp_mode)
	{
		tk->is_quoted = !tk->is_quoted;
		if (!tk->is_quoted)
			tk->is_quoted_dolar = 0;
	}
	else if ((*tk->data) == 34 && !tk->is_quoted && !tk->exp_mode)
		tk->is_dbl_quoted = !tk->is_dbl_quoted;
	else
		new_data = ft_chrjoin(new_data, *(tk->data));
	tk->data++;
	if (*tk->data && *tk->data == ' ' && !tk->is_quoted && !tk->is_dbl_quoted)
		tk->return_token = true;
	return (new_data);
}

static char	*dolar_handler(t_tokener *tk, char *new_data)
{
	tk->data++;
	if (*tk->data == ' ' || *tk->data == '\''
		|| (is_word_limit(*tk->data, LIM_DOLLAR)
			&& (*tk->data) != '?') || (*tk->data) == 92)
	{
		if ((*tk->data == '\'' || *tk->data == '\"')
			&& !tk->is_dbl_quoted && !tk->is_quoted)
		{
			if (*tk->data == '\'')
				tk->is_quoted_dolar = 1;
		}
		else
			new_data = ft_chrjoin(new_data, '$');
	}
	else
		get_expanded_dollar(tk);
	return (new_data);
}

static void	get_expanded_dollar(t_tokener *tk)
{
	char	*expanded;

	tk->data--;
	expanded = dolar_expansion(&tk->data,
			tk->master->env_list, ft_strdup(""));
	tk->exp_mode = 1;
	tk->data = str_pro_join(tk->data, expanded, 0);
	tk->end_expansion = tk->data + ft_strlen(expanded);
	free(expanded);
}

/*

// Si el siguiente caracter es NULL, avanzamos el dato sin escapar nada

// Cuando estamos entre comillas dobles NO se escapan los carcáteres 
// excepto '\$' y '\\'

// Escapamos el caracter, añadimos el caracter despues de la contrabarra 
// y nos posicionamos uno más allá.

*/

static char	*scape_handler(t_tokener *tk, char *new_data)
{
	char	to_scape;

	to_scape = *(tk->data + 1);
	if (to_scape == '\0')
		tk->data++;
	else if (tk->is_dbl_quoted && to_scape && to_scape != 34 \
			&& to_scape != '$' && to_scape != 92)
		new_data = ft_chrjoin(new_data, *tk->data++);
	else
	{
		if (tk->is_quoted_dolar)
		{
			if (is_especial(tk->data))
				new_data = ft_chrjoin(new_data, get_special(*(tk->data + 1)));
			tk->data++;
		}	
		else
			new_data = ft_chrjoin(new_data, *(++tk->data));
		tk->data++;
	}
	return (new_data);
}

static char	*tilde_handler(t_tokener *tk, char *new_data)
{
	char	*new_str;
	char	pre_tilde;
	char	post_tilde;

	post_tilde = *(tk->data + 1);
	pre_tilde = *(tk->data - 1);
	new_str = ft_strdup("");
	if ((tk->data == tk->original_promt
			&& (post_tilde == ' ' || post_tilde == '\0'))
		|| (pre_tilde == ' ' && (post_tilde == ' ' || post_tilde == '\0')))
		new_str = expand_tilde_home(tk, new_str);
	else if (post_tilde && pre_tilde == ' ')
		new_str = expand_tilde(tk, new_str);
	else
	{
		new_str = ft_chrjoin(new_str, *tk->data);
		tk->data++;
	}
	return (ft_strjoin_free(new_data, new_str));
}

static char	*expand_tilde_home(t_tokener *tk, char *new_str)
{
	char	*home_path;

	home_path = env_get_value(tk->master->env_list, "HOME");
	if (home_path == NULL)
		home_path = ft_strdup(tk->master->tild_value);
	new_str = ft_strjoin_free(new_str, home_path);
	(tk->data)++;
	return (new_str);
}

static char	*expand_tilde(t_tokener *tk, char *new_str)
{
	char	*expanded;
	int		pos;

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
	return (new_str);
}
