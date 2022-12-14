/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:29:10 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/11 03:07:43 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//	---- minishell.c
void	error(char *error, int num_error);
//void	error(t_master *master, char *error, int num_error);
t_node	*free_tree(t_node *node);
_Bool	init_node(t_node **node, int mode);
void	develop(t_node **node);

//	---- parser.c
_Bool	parser(t_node **list, char *parse_str, int reset);
t_node	*create_node(t_node **list, char *start, char *end, int node_id);
int		get_close_bracket(char *line);
int		get_operator(char *str);
_Bool	is_operator(char *str);
ssize_t	ffwd(char *start);
int		isquote(char *str, char quote);
int		isscaped(char *str);
void	set_top(t_node *node, t_node *top);
char	**expand_wildcard(char **command);

// ----- wilcard_utils.c
bool	match_wildcard( char *s,  char *pattern);

//	---- utils.c
//void 	print_tree(t_node *node);
void	free_split(char	**split);
void	print_parse_tree(t_node *node);
void	logtrace(char	*str1, char *str2, int param1, int param2);
char	*get_no_path(char *path);
char	*get_base_path(char *path);
char	*get_abs_path(char *path);
t_files	*list_dir_files(char *path);
void	*ft_realloc(void *ptr, size_t size);

//	---- executor.c
int		executor(t_node *node);
void	execute_child(t_node *node);
int		waiting_pipe(t_node *node);
int		is_post_op(t_node *node, int operator);
t_node	*execute_pipe(t_node *node, int *status);
t_node	*get_next(t_node *node, int operator);
char	*get_path(char	*cmd);
int		close_pipe_fd(int	*fd);
int		set_pipe(t_node	*node);

//	---- env.c
int		env_new_value(t_env **list, char *name, char *value);
void	env_set_value(t_env *list, char *name, char *value);
void	env_unset_value(t_env *list, char *name);
char	*env_get_value(t_env *list, char *name);
t_env	*env_search(t_env *list, char *name);
void	print_env(t_env *env_list);
void	env_free_list(t_env *list);
t_env	*env_parser(char **env);

char	**tokenizer(char *input);

#endif
