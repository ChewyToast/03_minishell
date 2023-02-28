#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

#include "structs.h"

_Bool	is_builtin(t_master *master, t_node *node);
_Bool	is_in_pipe(t_node *node);
_Bool	is_post_op(t_node *node, int operator);
t_node	*get_next(t_node *node, int operator);
_Bool	close_pipe_fd(int	*fd);

#endif