/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:43:17 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/08 20:57:32 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTORL_H
# define EXECUTORL_H

int		executor(t_master *master, t_node *node);
char	*str_dollar_expander(char *data, bool no_expand, t_env *env_list);
#endif
