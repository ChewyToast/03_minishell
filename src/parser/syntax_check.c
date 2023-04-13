/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:09:58 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/13 17:57:30 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"
#include "signals.h"

//private
static bool		dquote_expander(char **to_expand);
static int8_t	syntax_parser(char **input);
static void		syntax_parser_first_part(t_sypar *sypar);
static bool		syntax_parser_while(t_sypar *sypar);

#define UEOF "unexpected EOF while looking for matching `\"\'"
#define UEOF2 "ba.sh: syntax error: unexpected end of file"

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
	t_sypar	sypar;

	sypar.iter = *input;
	sypar.last_oper = *input;
	sypar.count = 0;
	sypar.squote = -1;
	sypar.dquote = -1;
	sypar.operator = -1;
	sypar.bracket = 0;
	if (syntax_parser_while(&sypar))
		return (1);
	if (sypar.operator == 32 && sypar.count)
		return (print_syntax_error(sypar.iter - sypar.count + 1, 1));
	if (!sypar.count && sypar.operator == 2)
		return (print_syntax_error("newline", 7));
	if (sypar.dquote > 0 || sypar.squote > 0 || sypar.bracket
		|| (!sypar.count && (sypar.operator == 1 || sypar.operator == 31)))
	{
		if (dquote_expander(input))
			return (1);
		return (2);
	}
	return (0);
}

static void	syntax_parser_first_part(t_sypar *sypar)
{
	if ((!get_operator_group(sypar->iter) || isscaped(sypar->iter))
		&& (!ft_isspace(*(sypar->iter)) || isscaped(sypar->iter)))
		sypar->count += 1;
	if (sypar->squote < 0 && isquote(sypar->iter, 34))
		sypar->dquote *= -1;
	else if (sypar->dquote < 0 && isquote(sypar->iter, 39))
		sypar->squote *= -1;
	else if (sypar->squote < 0 && sypar->dquote < 0
		&& *(sypar->iter) == '(' && !isscaped(sypar->iter))
		sypar->bracket -= 1;
	else if (sypar->squote < 0 && sypar->dquote < 0
		&& *(sypar->iter) == ')' && !isscaped(sypar->iter))
		sypar->bracket += 1;
}

static bool	syntax_parser_while(t_sypar *sypar)
{
	while (*(sypar->iter))
	{
		syntax_parser_first_part(sypar);
		if (sypar->bracket > 0)
			return (print_syntax_error(")", 1));
		if (sypar->dquote < 0 && sypar->squote < 0
			&& get_operator_group(sypar->iter) != 0)
			if (syntax_parser_operator_condition(sypar))
				return (1);
		sypar->iter++;
	}
	return (0);
}

static bool	dquote_expander(char **to_expand)
{
	char	*line;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	init_signals(INTERACTIVE);
	do_sigign(SIGQUIT);
	line = readline("> ");
	do_sigign(SIGINT);
	if (g_global.is_ctrlc)
	{
		g_global.num_return_error = 1;
		dup2(stdin_copy, STDIN_FILENO);
		return (1);
	}
	if (!line)
	{
		print_error(ft_strdup(UEOF), 1, 258);
		return (print_error(ft_strdup(UEOF2), 1, 258));
	}
	*to_expand = ft_strjoin_free(ft_strjoin_free(*to_expand,
				ft_strdup("\n")), line);
	if (*to_expand)
		return (0);
	return (1);
}
