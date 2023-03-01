/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:45 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/01 18:46:46 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "defines.h"

#define LIM_DOLLAR 1
#define LIM_WILDCARD 2
#define LIM_INIT 3


typedef struct s_tokener	t_tokener;

struct s_tokener
{
	char		*data;
	char		*end_expansion;
	t_master	*master;
	bool		is_quoted;
	bool		is_dbl_quoted;
	int			exp_mode;
	char		*original_promt;
	char		*full_data;
	bool		return_token;
};

char	*expand_wildcard(t_tokener *tk, char *new_data);
int		quotes_sub_handler(t_tokener *tk, char type);
char	*get_next_token(void);
char	*init_tokenizer(char *data_in, t_master *master);
char	*tknexp_init(char *data, t_tokener *tk, t_master *master, int reset);
void	pre_conditions(t_tokener *tk, char *new_data);
int		is_literal(t_tokener *tk);
char	*get_word_end(char *data, int type);
char	*get_word_init(char *data, char *data_min, int type);
bool	is_word_limit(char c, int type);
int		is_isolated_quotes(char	*data, char quote);


#endif
