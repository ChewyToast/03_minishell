/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:48:28 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/06 13:46:17 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "defines.h"
# include "utils.h"

char	*init_tokenizer(char *data_in, t_master *master, bool wildcard);
char	*get_next_token(bool wildcard);

bool	add_new_redirect(t_redirect *redirect, t_node *node);
void	add_redirect(t_redirect *redirect, t_redirect **node);
int		get_redirect_fd(char *start, char *end, char type);
int		extract_redirect(char **data, t_node *node, char *promt_init,
			t_master *master);
bool	redirect_expander(t_redirect *redirect, t_master *master);
bool	check_are_quotes(char *data);
char	*extractor_init(char *data, char **full_data, t_is *is);
char	*get_redirect_start(char *data, char *promt_init);
char	*get_redirect_end(char *data);
char	*check_quotes(char *data, bool *is_quoted, bool *is_dbl_quoted);
bool	is_redirect_limit(char c);
int		get_type_redirect(char **data);
char	*extract_redirects_and_clean(char *data, t_node *node,
			t_master *master);

#endif
