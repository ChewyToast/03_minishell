/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:43:53 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/05 17:50:07 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		isquote(char *str, char quote);
int		isscaped(char *str);
void	*ft_realloc(void *ptr, size_t size);
t_node	*free_tree(t_node *node);
int		free_split(char	**split);
t_files	*list_dir_files(char *path);
char	*get_abs_path(char *path);
char	*get_base_path(char *path);
char	*get_no_path(char *path);
char	*ft_strjoin_free(char *str1, char *str2);
char	*ft_chrjoin(char *str, char c);
char	*str_pro_join(char *str1, char *str2, int pos);
int		pre_spaces_clean(char **data);
int		spaces_clean_back(char **data, char *str_ini);
int		spaces_clean(char **data);
void	print_parse_tree(t_node *node);
void	exit_program(char *data, bool print_msg, int err_num);
bool	print_error(char *data, bool print_msg, int err_num);
void	str_to_lower(char *str);
int		is_numeric(char *inp);
bool	is_especial(char *str);
char	get_special(char c);
long	ft_atoi_long_long(const char *nptr);
bool	is_free_char(t_is is);

#endif
