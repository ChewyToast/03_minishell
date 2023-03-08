/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:01 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/08 17:43:34 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

bool	is_builtin(t_master *master, t_node *node);
bool	is_in_pipe(t_node *node);
bool	is_post_op(t_node *node, int operator);
t_node	*get_next(t_node *node, int operator);
bool	close_pipe_fd(int	*fd);

#endif
