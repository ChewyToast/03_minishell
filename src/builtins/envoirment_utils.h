/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoirment_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:44:39 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/05 13:37:18 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVOIRMENT_UTILS_H
# define ENVOIRMENT_UTILS_H

void	prepare_next_export(t_node *node);
int8_t	set_new_values(t_master *master, char *name, char *value);
char	**sort_env(char **env);
int		print_export(t_master *master);
void	free_envc(char	**envc);

#endif
