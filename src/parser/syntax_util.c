/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:29:57 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:39:49 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	syntax_parser_operator_condition(t_sypar *sypar)
{
	if (sypar->operator == 2 && !sypar->count)
		return (print_syntax_error("newline", 7));
	if (sypar->operator == -1 && !sypar->count
		&& get_operator_group(sypar->iter) == 1)
		return (print_syntax_error(sypar->iter, 2));
	if (sypar->operator == 31
		&& !sypar->count && get_operator_group(sypar->iter) == 1)
		return (print_syntax_error(sypar->iter, 2));
	if (extra_operator_condition(sypar))
		return (1);
	sypar->operator = get_operator_group(sypar->iter);
	if (sypar->operator != 31 && sypar->operator != 32 && *(sypar->iter)
		&& *(sypar->iter + 1) && *(sypar->iter) == *(sypar->iter + 1))
		sypar->iter++;
	sypar->last_oper = sypar->iter;
	sypar->count = 0;
	return (0);
}

bool	extra_operator_condition(t_sypar *sypar)
{
	if (sypar->operator == 31
		&& !sypar->count && get_operator_group(sypar->iter) == 32)
		return (print_syntax_error(sypar->iter, 1));
	if (sypar->operator == 32 && sypar->count
		&& get_operator_group(sypar->iter) == 2
		&& get_redirect_start(sypar->iter, sypar->last_oper) == sypar->iter)
		return (print_syntax_error(sypar->iter, 1));
	if (sypar->operator == 32 && sypar->count
		&& get_operator_group(sypar->iter) != 2)
		return (print_syntax_error(sypar->iter, 1));
	if (sypar->operator == 1
		&& !sypar->count && get_operator_group(sypar->iter) == 1)
		return (print_syntax_error(sypar->iter, 1));
	return (0);
}

int8_t	get_operator_group(char *str)
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

bool	print_syntax_error(char *to_print, int8_t size)
{
	write(2, "ba.sh: syntax error near unexpected token `", 43);
	write(2, to_print, size);
	write(2, "'\n", 2);
	g_global.num_return_error = 258;
	return (1);
}
