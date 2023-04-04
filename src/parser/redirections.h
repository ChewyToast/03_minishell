/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:48:28 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/04 13:29:57 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

char	*get_redirect_start(char *data, char *promt_init);
char	*get_redirect_end(char *data);
char	*check_quotes(char *data, bool *is_quoted, bool *is_dbl_quoted);
bool	is_redirect_limit(char c);
int		get_type_redirect(char **data);
char	*extract_redirects_and_clean(char *data, t_node *node,
			t_master *master);

#endif
