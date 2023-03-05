/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:09:58 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/03/05 16:32:25 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "signals.h"
#include "readline.h"

// static bool		syntax_input(char *input);
// static bool		syntax_dquote(char **input);
// static bool		syntax_operators(char *input);
static int8_t	get_operator_group(char *str);
static bool		dquote_expander(char **to_expand);
static int8_t	syntax_parser(char **input);

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
	int8_t	util;

	util = syntax_parser(input);
	while (util == 2)
		util = syntax_parser(input);
	return (util);
}

static int8_t	syntax_parser(char **input)
{
	char	*iter;
	size_t	count;
	int8_t	squote;
	int8_t	dquote;
	int8_t	operator;
	int		bracket;

	iter = *input;
	count = 0;
	squote = -1;
	dquote = -1;
	operator = -1;
	bracket = 0;
	while (*iter)
	{
		if ((!get_operator_group(iter) || isscaped(iter)) && (!ft_isspace(*iter) || isscaped(iter)))
			count += 1;
		if (squote < 0 && isquote(iter, 34))
			dquote *= -1;
		else if (dquote < 0 && isquote(iter, 39))
			squote *= -1;
		else if (squote < 0 && dquote < 0 && *iter == '(')
			bracket -= 1;
		else if (squote < 0 && dquote < 0 && *iter == ')')
			bracket += 1;
		if (bracket > 0)
			{ft_printf("ba.sh: syntax error near token `%c'\n", *iter); return (1);}
		if (dquote < 0 && squote < 0 && get_operator_group(iter) != 0)
		{
			if (operator == 2 && !count)
				{ft_printf("ba.sh: syntax error near token `%c'\n", *iter); return (1);}
			if (operator == -1 && !count && get_operator_group(iter) == 1)
				{ft_printf("ba.sh: syntax error near token `%c'\n", *iter); return (1);}
			if (operator == 3 && count && get_operator_group(iter) == 1)
				{ft_printf("ba.sh: syntax error near token `%c'\n", *iter); return (1);}
			if (operator == 3 && !count && get_operator_group(iter) == 3)
				{ft_printf("ba.sh: syntax error near token `%c'\n", *iter); return (1);}
			if (operator == 1 && !count && get_operator_group(iter) == 1)
				{ft_printf("ba.sh: syntax error near token `%c'\n", *iter); return (1);}
			operator = get_operator_group(iter);
			if (operator != 3 && *(iter) && *(iter + 1) && *(iter) == *(iter + 1))
				iter++;
			count = 0;
		}
		iter++;
	}
	if (dquote > 0 || squote > 0 || bracket || (!count && operator != 3))
	{
		if (dquote_expander(input))
			return (1);
		return (2);
	}
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

static bool	dquote_expander(char **to_expand)
{
	char *line;

	init_signals(INTERACTIVE);
	line = readline("> ");
	init_signals(NO_INTERACTIVE);
	if (global.is_ctrlC)
		return (1);
	if (!line)
		return (print_error(ft_strdup("ba.sh: unexpected EOF while looking for matching `\"\'\nba.sh: syntax error: unexpected end of file"), 1));
	*to_expand = ft_strjoin_free(ft_strjoin_free(*to_expand, ft_strdup("\n")), line);
	if (*to_expand)
		return (0);
	return (1);
}
