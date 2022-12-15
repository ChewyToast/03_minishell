/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 23:29:10 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/15 14:55:40 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//	---- minishell.c
void 	error(t_node *node, char *error);
void    free_tree(t_node *node);
_Bool	init_node(t_node **node);

//	---- parser.c
_Bool	parser(t_node *node, char *input, size_t len);

//	---- utils.c
void 	print_tree(t_node *node);
void	free_split(char	**split);

//	---- env.c
t_env	*env_parser(char **env);
void	env_free_list(t_env *list);
t_env	*env_search(t_env *list, char *name);
t_env	*env_new_value(t_env *list, char *name, char *value);

#endif