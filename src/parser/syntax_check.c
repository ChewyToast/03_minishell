/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:09:58 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/03 20:23:28 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "signals.h"
#include "readline.h"

static int8_t	get_operator_group(char *str);
static bool		dquote_expander(char **to_expand);
static int8_t	syntax_parser(char **input);
static bool		print_syntax_error(char *to_print, int8_t size);

/*
	ENFOQUE AL REVES, VAMOS A BUSCAR LOS CASOS QUE NO PUEDEN SER

	"&&"  <-/->  "||"  <-/->  "|"

		^		^		^
		|		|		|
		|		v		|
		|				|
		|  <-/->  "()"	|
		|				|
		|		^		|
		|		|		|
		v		v		v

	"< >"      <-->     "<< >>"
*/

bool	syntax_check(char **input)
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
	int		squote;
	int		dquote;
	int		operator;
	int		bracket;

	iter = *input;
	count = 0;
	squote = -1;
	dquote = -1;
	operator = -1;
	bracket = 0;
	while (*iter)
	{
		if ((!get_operator_group(iter) || isscaped(iter))
			&& (!ft_isspace(*iter) || isscaped(iter)))
			count += 1;
		if (squote < 0 && isquote(iter, 34))
			dquote *= -1;
		else if (dquote < 0 && isquote(iter, 39))
			squote *= -1;
		else if (squote < 0 && dquote < 0 && *iter == '(' && !isscaped(iter))
			bracket -= 1;
		else if (squote < 0 && dquote < 0 && *iter == ')' && !isscaped(iter))
			bracket += 1;
		if (bracket > 0)
			return (print_syntax_error(")", 1));
		if (dquote < 0 && squote < 0 && get_operator_group(iter) != 0)
		{
			if (operator == 2 && !count)
				return (print_syntax_error("newline", 7));
			if (operator == -1 && !count && get_operator_group(iter) == 1)
				return (print_syntax_error(iter, 2));
			if (operator == 31 && !count && get_operator_group(iter) == 1)
				return (print_syntax_error(iter, 2));
			if (operator == 31 && !count && get_operator_group(iter) == 32)
				return (print_syntax_error(iter, 1));
			if (operator == 32 && count)
				return (print_syntax_error(iter, 1));
			if (operator == 1 && !count && get_operator_group(iter) == 1)
				return (print_syntax_error(iter, 1));
			operator = get_operator_group(iter);
			if (operator != 31 && operator != 32 && *(iter)
				&& *(iter + 1) && *(iter) == *(iter + 1))
				iter++;
			count = 0;
		}
		iter++;
	}
	if (operator == 32 && count)
		return (print_syntax_error(iter - count + 1, 1));
	if (!count && operator == 2)
		return (print_syntax_error("newline", 7));
	if (dquote > 0 || squote > 0 || bracket
		|| (!count && (operator == 1 || operator == 31)))
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
	if (*str == '|' && *(str + 1) && *(str + 1) == '|' && !isscaped(str))
		return (1);
	if (*str == '&' && *(str + 1) && *(str + 1) == '&' && !isscaped(str))
		return (1);
	if (*str == '|' && (!*(str + 1) || *(str + 1) != '|') && !isscaped(str))
		return (1);
	if (*str == '<' && (!*(str + 1) || *(str + 1) != '<') && !isscaped(str))
		return (2);
	if (*str == '<' && *(str + 1) && *(str + 1) == '<' && !isscaped(str))
		return (2);
	if (*str == '>' && (!*(str + 1) || *(str + 1) != '>') && !isscaped(str))
		return (2);
	if (*str == '>' && *(str + 1) && *(str + 1) == '>' && !isscaped(str))
		return (2);
	if (*str == ')' && !isscaped(str))
		return (32);
	if (*str == '(' && !isscaped(str))
		return (31);
	return (0);
}

static bool	dquote_expander(char **to_expand)
{
	char	*line;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	init_signals(HERE_DOC);
	line = readline("> ");
	init_signals(NO_INTERACTIVE);
	if (global.is_ctrlC)
	{
		dup2(stdin_copy, STDIN_FILENO);
		global.is_ctrlC = 0;
		return (1);
	}
	if (!line)
		return (print_error(ft_strdup("unexpected EOF while looking for \
		matching `\"\'\nba.sh: syntax error: unexpected end of file"), 1, 258));
	*to_expand = ft_strjoin_free(ft_strjoin_free(*to_expand,
				ft_strdup("\n")), line);
	if (*to_expand)
		return (0);
	return (1);
}

static bool	print_syntax_error(char *to_print, int8_t size)
{
	write(2, "ba.sh: syntax error near unexpected token `", 43);
	write(2, to_print, size);
	write(2, "'\n", 2);
	global.num_return_error = 258;
	return (1);
}
