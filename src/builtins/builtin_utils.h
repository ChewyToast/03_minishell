/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:44:39 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/03 17:26:08 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H

bool	is_valid_name(char *str);
char	*get_current_pwd(void);
int		get_export_values(t_node *node, char **name, char **value);

#endif
