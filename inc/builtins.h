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