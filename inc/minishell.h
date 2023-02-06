/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:29:10 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/02/06 20:48:36 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "structs.h"

int		num_return_error;

// 	ESTE HEADER ESTA HORRIBLE... CULPA MIA PERO AHORA NO LO QUIERO ARREGLAR
_Bool	syntax_check(char *input);
char	extra_operator(char *input);
char	*check_cmd(t_master *master, t_node *node);
int		exec_cd(t_master *master,t_node	*node);
int		exec_pwd(t_node *node);
int		exec_echo(t_node *node);
int		exec_echo(t_node *node);
char	*get_current_pwd(void);
int		exec_export(t_master *master, t_node *node);
int		get_export_values(t_node *node, char **name, char **value);
int		exec_unset(t_master *master, t_node *node);
int		exec_exit(t_master *master, t_node *node);
void	add_bash_lvl(t_master *master, t_env *node);
void	default_env(t_master *master);
char	*get_token(char **data);

//	---- minishell.c
void	error(char *error, int num_error);
void 	exit_program(char *msg_error, int num_error);
//void	error(t_master *master, char *error, int num_error);
t_node	*free_tree(t_node *node);
_Bool	init_node(t_node **node, int mode);
void	develop(t_node **node);

//	---- redirects.c
bool	extract_redirect(char **data, t_node *node);
char	*extract_redirects_and_clean(char *data, t_node *node);

//	---- parser.c
_Bool	parser(t_node **list, char *parse_str, int reset);
t_node	*create_node(t_node **list, char *start, char *end, int node_id);
int		get_close_bracket(char *line);
int		get_operator(char *str);
ssize_t	ffwd(char *start);
int		isquote(char *str, char quote);
int		isscaped(char *str);
void	set_top(t_node *node, t_node *top);
char	*expand_str_wildcard(char *token);

// ----- wilcard_utils.c
bool	match_wildcard(char *s, char *pattern);

//	---- utils.c
//void 	print_tree(t_node *node);
void	free_split(char	**split);
void	print_parse_tree(t_node *node);
void	logtrace(char *str1, char *str2, int param1, int param2);
char	*get_no_path(char *path);
char	*get_base_path(char *path);
char	*get_abs_path(char *path);
t_files	*list_dir_files(char *path);
void	*ft_realloc(void *ptr, size_t size);
int		is_numeric(char *inp);
char	*ft_chrjoin(char *str, char	c);
int		spaces_clean(char **data);
char	*ft_strjoin_free(char *str1, char	*str2);
int		ft_strcmp(const char *s1, const char *s2);
void	str_to_lower(char *str);
int	pre_spaces_clean(char **data);

//	---- expander.c
char	*get_next_token();
char	*init_tokenizer(char *data_in, t_master *master);

//	---- executor.c
int		executor(t_master *master, t_node *node);
int		execute_command(t_master *master, t_node *node);
int		exec(t_master *master, t_node *node);
t_node	*get_next(t_node *node, int operator);
_Bool	close_pipe_fd(int *fd);
_Bool	is_post_op(t_node *node, int operator);
_Bool	is_in_pipe(t_node *node);
_Bool	is_builtin(t_master *master, t_node *node);

//	---- env.c
int		env_new_value(t_env **list, char *name, char *value);
void	env_set_value(t_env *list, char *name, char *value);
void	env_unset_node(t_master *master, char *name);
char	**env_get_path(t_env *list);
char	*env_get_value(t_env *list, char *name);
t_env	*env_search(t_env *list, char *name);
void	print_env(t_env *env_list);
void	env_free_list(t_env *list);
t_env	*env_parser(char **env);
char	**env_to_array(t_env *list);
_Bool	env_change_value(t_env	*list, char *name, char *value);
char	**tokenizer(char *input);


//	---- signals.c
int	init_signals(int mode);

#endif
