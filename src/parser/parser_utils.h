#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

void	set_top(t_node *node, t_node *top);
int		isquote(char *str, char quote);
int		isscaped(char *str);
int		get_operator(char *str);
int		get_close_bracket(char *line);

#endif