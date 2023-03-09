/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:59 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/09 13:56:20 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

bool	prepare_redirect(t_fdmanage **fdman, t_redirect *redi, t_env *env_list);
bool	close_fdman(t_fdmanage **fdman, int index);
bool	add_fdman(t_fdmanage **fdman, int index, int fd);

#endif
