/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:43:04 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/01 18:43:06 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

t_env	*env_parser(char **env);
char	**env_to_array(t_env *list);
void	env_free_list(t_env *list);
char	*env_get_value(t_env *list, char *name);
void	env_set_value(t_env **list, char *name, char *value);
char	**env_get_path(t_env *list);
void	env_free_list(t_env *list);
void	env_unset_node(t_master *master, char *name);
t_env	*env_search(t_env *list, char *name);
_Bool	env_change_value(t_env	*list, char *name, char *value);
int		env_new_value(t_env **list, char *name, char *value);

#endif
