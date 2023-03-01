/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:42:51 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/01 18:42:54 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int	exec_cd(t_master *master,t_node	*node);
int	exec_pwd(t_node *node);
int	exec_echo(t_node *node);
int	exec_echo(t_node *node);
int	exec_unset(t_master *master, t_node *node);
int	exec_exit(t_master *master, t_node *node);
int	exec_export(t_master *master, t_node *node);

#endif
