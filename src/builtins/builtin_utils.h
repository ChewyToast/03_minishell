/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:44:39 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/01 18:44:40 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BULTIN_UTILS_H
# define BULTIN_UTILS_H

bool	isalphanum(char *str);
char	*get_current_pwd(void);
int		get_export_values(t_node *node, char **name, char **value);

#endif
