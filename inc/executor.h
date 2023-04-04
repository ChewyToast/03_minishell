/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:43:17 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/04 13:55:43 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		executor(t_master *master, t_node *node);
char	*str_dollar_expander(char *data, bool no_expand, t_env *env_list);
#endif
