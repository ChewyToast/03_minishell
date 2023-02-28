/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:09:58 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/02/28 22:49:41 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

static bool		syntax_input(char *input);
static bool		syntax_dquote(char **input);
static bool		syntax_operators(char *input);
static int8_t	get_operator_group(char *str);

/*

	ENFOQUE AL REVES, VAMOS A BUSCAR LOS CASOS QUE NO PUEDEN SER

	"&&"  <-/->  "||"  <-/->  "|"	1-TIPO UNO, NO PUEDEN ESTAR UNIDOS POR 0 CARACTERES ENTRE ELLOS PERO SI CON TIPO DOS

		^		^		^
		|		|		|
		|		v		|
		|				|
		|  <-/->  "()"	|			3-TIPO TRES, NO PUEDEN ESTAR UNIDOS
		|				|
		|		^		|
		|		|		|
		v		v		v

	"< >"      <-->     "<< >>" 	2-TIPO DOS, PUEDEN ESTAR UNIDOS POR 0 CARACTERES ENTRE ELLOS Y ENTRE TODOS LOS TIPOS

*/

_Bool	syntax_check(char **input)
{
	if (syntax_input(*input))
		return (1);
	while (syntax_dquote(input))
		if (syntax_input(*input))
			return (1);
	if (syntax_operators(*input))
		return (1);
	return (0);
}

static bool	syntax_input(char *input)
// FALTA CHECKEAR PARENTESIS NO NECESARIOS COMO ((ECHO HOLA)) (esto es syntax error)
{
	size_t	count;

	while (*input)
	{
		count = 1;
		if (*input == '|' && !isscaped(input))// check for OR
			while (*(++input) == '|')
				count++;
		else if (*input == '&' && !isscaped(input))// check for AND
			while (*(++input) == '&')
				count++;
		else if (*input == '<' && !isscaped(input))// check for <
			while (*(++input) == '<')
				count++;
		else if (*input == '<' && !isscaped(input))// check for >
			while (*(++input) == '>')
				count++;
		else
			input += 1;
		if (count > 2)
			{ft_printf("syntax error near token `%c'\n", *(input - (count - 1))); return (1);}
	}
	return (0);
}

static bool	syntax_dquote(char **input)
// FALTA HACER DQUOTE QUANDO ACABA EN OPERADOR, NO SOLO COMILLAS Y PARENTESIS
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
		return (0);
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
	operator = -1;
	while (*input)
	{
		if ((!get_operator_group(input) || isscaped(input)) && (!ft_isspace(*input) || isscaped(input)))
			count += 1;
		if (squote < 0 && isquote(input, 34))
			dquote *= -1;
		else if (dquote < 0 && isquote(input, 39))
			squote *= -1;
		if (dquote < 0 && squote < 0 && get_operator_group(input) != 0)
		{
			if (operator == 2 && !count)
				return (1);
			if (operator == -1 && !count && get_operator_group(input) == 1)
				return (1);
			if (operator == 3 && count && get_operator_group(input) == 1)
				return (1);
			if (operator == 3 && !count && get_operator_group(input) == 3)
				return (1);
			if (operator == 1 && !count && get_operator_group(input) == 1)
				return (1);
			operator = get_operator_group(input);
			if (*input == *(input + 1))
				input++;
			count = 0;
		}
		input++;
	}
	if (!count && operator != 3)
		return (1);
	return (0);
}

static int8_t	get_operator_group(char *str)
{
	if (!*str)
		return (1);
	if (*str == '|' && *(str + 1) && *(str + 1) == '|' && !isscaped(str))// check for OR
		return (1);
	if (*str == '&' && *(str + 1) && *(str + 1) == '&' && !isscaped(str))// check for AND
		return (1);
	if (*str == '|' && (!*(str + 1) || *(str + 1) != '|') && !isscaped(str))// check for PIP
		return (1);
	if (*str == '<' && (!*(str + 1) || *(str + 1) != '<') && !isscaped(str))// check for <
		return (2);
	if (*str == '<' && *(str + 1) && *(str + 1) == '<' && !isscaped(str))// check for <<
		return (2);
	if (*str == '>' && (!*(str + 1) || *(str + 1) != '>') && !isscaped(str))// check for >
		return (2);
	if (*str == '>' && *(str + 1) && *(str + 1) == '>' && !isscaped(str))// check for >>
		return (2);
	if (*str == ')' && !isscaped(str))// check for )
		return (3);
	if (*str == '(' && !isscaped(str))// check for (
		return (3);
	return (0);
}
