/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:42:51 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/04 13:55:30 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	exec_cd(t_master *master, t_node *node);
int	exec_pwd(t_node *node);
int	exec_echo(t_node *node);
int	exec_echo(t_node *node);
int	exec_unset(t_master *master, t_node *node);
int	exec_exit(t_master *master, t_node *node);
int	exec_export(t_master *master, t_node *node);
int	exec_env(t_master *master, t_node *node);

#endif
