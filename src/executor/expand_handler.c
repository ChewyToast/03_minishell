/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:09:34 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:21:39 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "expander.h"
#include "utils.h"
#include "expand_handler.h"
#include "bmlib.h"

void	get_expanded_dollar(t_tokener *tk);
char	*expand_tilde(t_tokener *tk, char *new_str);
char	*expand_tilde_home(t_tokener *tk, char *new_str);

char	*tilde_handler(t_tokener *tk, char *new_data)
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

char	*scape_handler(t_tokener *tk, char *new_data)
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

char	*quotes_handler(t_tokener *tk, char	*new_data)
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

char	*dolar_handler(t_tokener *tk, char *new_data)
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
