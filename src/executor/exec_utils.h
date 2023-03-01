/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:01 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/01 18:46:02 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

_Bool	is_builtin(t_master *master, t_node *node);
_Bool	is_in_pipe(t_node *node);
_Bool	is_post_op(t_node *node, int operator);
t_node	*get_next(t_node *node, int operator);
_Bool	close_pipe_fd(int	*fd);

#endif
