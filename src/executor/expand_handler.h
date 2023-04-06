/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:12:41 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:20:46 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_HANDLER_H
# define EXPAND_HANDLER_H

char	*tilde_handler(t_tokener *tk, char *new_data);
char	*scape_handler(t_tokener *tk, char *new_data);
char	*quotes_handler(t_tokener *tk, char	*new_data);
char	*dolar_handler(t_tokener *tk, char *new_data);

#endif
