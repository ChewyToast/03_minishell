/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:43:53 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/01 18:43:54 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H


int		isquote(char *str, char quote);
int		isscaped(char *str);
void	*ft_realloc(void *ptr, size_t size);
t_node	*free_tree(t_node *node);
void	free_split(char	**split);
t_files	*list_dir_files(char *path);
char	*get_abs_path(char *path);
char	*get_base_path(char *path);
char	*get_no_path(char *path);
char	*ft_strjoin_free(char	*str1, char	*str2);
char	*ft_chrjoin(char	*str, char	c);
char	*str_pro_join(char *str1, char *str2, int pos);
int		pre_spaces_clean(char **data);
int		spaces_clean_back(char **data, char *str_ini);
int		spaces_clean(char **data);
void	print_parse_tree(t_node *node);
void 	exit_program(char *msg_error, int num_error);
int		print_error(char *error, int num_error);
void	str_to_lower(char *str);
int		is_numeric(char *inp);

#endif