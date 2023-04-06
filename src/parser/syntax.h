/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:31:52 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:36:25 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "defines.h"
# include "utils.h"
# include "signals.h"
# include "readline.h"

typedef struct s_sypar	t_sypar;
bool			syntax_parser_operator_condition(t_sypar *sypar);
bool			extra_operator_condition(t_sypar *sypar);
char			*get_redirect_start(char *data, char *promt_init);
int8_t			get_operator_group(char *str);
bool			print_syntax_error(char *to_print, int8_t size);

struct s_sypar
{
	char	*iter;
	char	*last_oper;
	int		squote;
	int		dquote;
	int		operator;
	int		bracket;
	size_t	count;
};

#endif
