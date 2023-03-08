/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:59 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/08 17:35:46 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

bool	prepare_redirect(t_fdmanage **fdman, t_redirect *redi);
bool	close_fdman(t_fdmanage **fdman, int index);
bool	add_fdman(t_fdmanage **fdman, int index, int fd);

#endif
