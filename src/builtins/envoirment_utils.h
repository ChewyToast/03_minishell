/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoirment_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:44:39 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/05 17:57:04 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVOIRMENT_UTILS_H
# define ENVOIRMENT_UTILS_H

void	prepare_next_export(t_node *node);
void	set_new_values(t_master *master, char *name, char *value);
char	**sort_env(char **env);
int		print_export(t_master *master);
void	free_envc(char	**envc);

#endif
