
#ifndef BULTIN_UTILS_H
# define BULTIN_UTILS_H
#include "structs.h"

bool	isalphanum(char *str);
char	*get_current_pwd(void);
int		get_export_values(t_node *node, char **name, char **value);

#endif