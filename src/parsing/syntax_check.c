/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:09:58 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/02/07 18:54:23 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

/*

	"&&"  <-/->  "||"  <-/->  "|"

		^		^		^
		|		|		|
		v		v		v

	"()"  <-->  "< >"  <--> "<< >>"

*/

_Bool	syntax_check(char **input)
{
	while (syntax_dquote(input));
	// if (syntax_operators(*input))
		// return (1);
}

static bool	syntax_dquote(char **input)
{
	char	*iter;
	int8_t	squote;
	int8_t	dquote;
	int8_t	bracket;

	iter = *input
	squote = -1;
	dquote = -1;
	bracket = 0;
	while (*iter)
	{
		if (squote < 0 && isquote(iter, 34))
			dquote *= -1;
		else if (dquote < 0 && isquote(iter, 39))
			squote *= -1;
		else if (squote < 0 && dquote < 0 && *input == '(')
			bracket -= 1;
		else if (squote < 0 && dquote < 0 && *input == ')')
			bracket += 1;
		iter++;
	}
	if (dquote > 0 || squote > 0 || bracket)
	{
		dquote_expander(input);
		return (1);
	}
	return (0);
}




























static	bool	simple(char *input)
{
	char	*tmp;
	int		syntax_key;

	tmp = input;
	syntax_key = 0;
	while (*input)
	{
		if (*input == 92)
			input += 2;// IMPORTANTE, PARA QUE NO SEG FAULT/BUS ERROR HAY QUE HACER DEQUOTE PARA BARRA ESCAPE AL FINAL DE LINEA
		if (*input && is_syntax_key(*input))
		{
			if (!syntax_key)
			{
				syntax_key = *input;
				tmp = input;
			}
			else
			{
				if (its)
			}
		}
	}
}

static bool	verify_content(char *start, char *end)
{
	size_t	count;

	count = 0;
	while (*start && start < end)
	{
		if (!ft_isspace(*(start)) || isscaped(start))
			count++;
		start++;
	}
	if (start)
		return (true);
	return (false);
}

static	int	is_syntax_key(char *character)
{
	if (!*str)
		return (TEND);
	if (*str == '|' && *(str + 1) && *(str + 1) == '|'
		&& !isscaped(str))
		return (TOR);
	if (*str == '&' && *(str + 1) && *(str + 1) == '&'
		&& !isscaped(str))
		return (TAND);
	if (*str == '|' && (!*(str + 1) || *(str + 1) != '|')
		&& !isscaped(str))
		return (TPIP);
	return (TUNDEF);
}