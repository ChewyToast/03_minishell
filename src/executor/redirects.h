/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:59 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/03 19:39:03 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

bool	prepare_redirect(t_redirect *redi, t_env *env_list);
bool	close_fdman(t_fdmanage **fdman, int index);
bool	add_fdman(t_fdmanage **fdman, int index, int fd);

#endif
