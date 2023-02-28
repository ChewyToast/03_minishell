/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:09:58 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/02/19 14:09:56 by test             ###   ########.fr       */
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

static bool	syntax_dquote(char **input);
static bool	syntax_operators(char *input);

_Bool	syntax_check(char **input)
{
	while (syntax_dquote(input));
	if (syntax_operators(*input))
		return (1);
	return (0);
}

static bool	syntax_dquote(char **input)
{
	char	*iter;
	int8_t	squote;
	int8_t	dquote;
	int8_t	bracket;

	iter = *input;
	squote = -1;
	dquote = -1;
	bracket = 0;
	while (*iter)
	{
		if (squote < 0 && isquote(iter, 34))
			dquote *= -1;
		else if (dquote < 0 && isquote(iter, 39))
			squote *= -1;
		else if (squote < 0 && dquote < 0 && *iter == '(')
			bracket -= 1;
		else if (squote < 0 && dquote < 0 && *iter == ')')
			bracket += 1;
		if (bracket > 0)
		{
			ft_printf("SYNTAX ERROR FOR ')' FOUND BEFORE '('\n");
			exit(0);
		}
		iter++;
	}
	if (dquote > 0 || squote > 0 || bracket)
	{
		// dquote_expander(input);
		// return (1);
		ft_printf("DQUOTE!\n");
		exit(0);
	}
	return (0);
}

static bool	syntax_operators(char *input)
{
	size_t	count;
	int8_t	squote;
	int8_t	dquote;
	int8_t	operator;

	count = 0;
	squote = -1;
	dquote = -1;
	operator = TUNDEF;
	while (*iter)
	{
		if (!ft_isspace(*iter) || isscaped(iter))
			count += 1;
		if (squote < 0 && isquote(iter, 34))
			dquote *= -1;
		else if (dquote < 0 && isquote(iter, 39))
			squote *= -1;
		if (dquote < 0 && squote < 0 && get_operator(iter) != 0)
		{
			if (syntax_compatible(&operator, get_operator(iter), count, &input))
			count = 0;
		}
		iter++;
	}
}

static bool syntax_compatible(int8_t *last, int new, size_t count, char **input)
{
	if (*last == 0)
	{
		*last == new;
		*input += 1;
		if (new > 2)
			*input += 1;
		return (0);
	}
	if (*last == TPIP)
		return (syntax_pip_case());
	if (*last == TOR)
		return (syntax_or_case());
	if (*last == TAND)
		return (syntax_and_case());
	return (0);
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
	if (count)
		return (true);
	return (false);
}

// ANOTAMOS <<< TRIPLE ES UN STRING SINO SE USA ES UN ERROR NEAR TOKEN BLA BLA BLA

/*

	"&&"  <-/->  "||"  <-/->  "|"

		^		^		^
		|		|		|
		v		v		v

	"()"  <-->  "< >"  <--> "<< >>"


Encontramos un operador, y buscamos el siguiente, miramos cada caso que debe pasar
y el siguiente pasa a ser el actual;

*/



// static	int	is_syntax_key(char *character)
// {
// 	if (!*str)
// 		return (TEND);
// 	if (*str == '|' && *(str + 1) && *(str + 1) == '|'
// 		&& !isscaped(str))
// 		return (TOR);
// 	if (*str == '&' && *(str + 1) && *(str + 1) == '&'
// 		&& !isscaped(str))
// 		return (TAND);
// 	if (*str == '|' && (!*(str + 1) || *(str + 1) != '|')
// 		&& !isscaped(str))
// 		return (TPIP);
// 	return (TUNDEF);
// }
// static	bool	simple(char *input)
// {
// 	char	*tmp;
// 	int		syntax_key;

// 	tmp = input;
// 	syntax_key = 0;
// 	while (*input)
// 	{
// 		if (*input == 92)
// 			input += 2;// IMPORTANTE, PARA QUE NO SEG FAULT/BUS ERROR HAY QUE HACER DEQUOTE PARA BARRA ESCAPE AL FINAL DE LINEA
// 		if (*input && is_syntax_key(*input))
// 		{
// 			if (!syntax_key)
// 			{
// 				syntax_key = *input;
// 				tmp = input;
// 			}
// 			else
// 			{
// 				if (its)
// 			}
// 		}
// 	}
// }
