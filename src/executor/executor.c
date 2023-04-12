/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:38:16 by aitoraudi         #+#    #+#             */
/*   Updated: 2023/04/06 13:25:35 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "exec_utils.h"
#include "exec_cmd.h"
#include "signals.h"
#include "expander.h"
#include "redirects.h"
#include "utils.h"

int				waiting_pipe(t_node *node);

//	---- local headers
static t_node	*execute_pipe(t_master *master, t_node *node, int *status,
					t_node *node_init);
static void		execute_child(t_master *master, t_node *node);
static int		set_pipe(t_node	*node, t_env *env_list);
static t_node	*builtin_exec(t_master *master, t_node *node, int *status);

//	---- public
int	executor(t_master *master, t_node *node)
{
	int		status;

	while (node)
	{
		node = execute_pipe(master, node, &status, node);
		if (node && is_post_op(node, TAND))
		{
			if (status > 0)
				node = get_next(node, TOR);
		}
		else if (node && is_post_op(node, TOR))
		{
			if (!status)
				node = get_next(node, TAND);
		}
	}
	return (status);
}

//	---- private
// @to_do hay que limitar que no se pueda abrir mas que 199
static t_node	*execute_pipe(t_master *master, t_node *node,
		int *status, t_node *node_init)
{
	if (!node)
		return (NULL);
	if (!is_in_pipe(node) && !node->subshell && is_builtin(master, node))
		return (builtin_exec(master, node, status));
	while (node)
	{
		if (node->operator == TPIP)
			pipe(node->fd);
		node->pid = fork();
		if (node->pid < 0)
			exit_program(NULL, 0, 1);
		if (node->pid == 0)
			execute_child(master, node);
		if (node->prev && node->prev->operator == TPIP)
			close_pipe_fd(node->prev->fd);
		if (node->operator != TPIP)
			break ;
		node = node->next;
	}
	g_global.is_ctrlc = 0;
	*status = waiting_pipe(node_init);
	g_global.num_return_error = *status;
	if (node)
		return (node->next);
	return (NULL);
}

static t_node	*builtin_exec(t_master *master, t_node *node, int *status)
{
	int		old_infd;
	int		old_outfd;

	old_infd = dup2(STDIN_FILENO, 200);
	old_outfd = dup2(STDOUT_FILENO, 201);
	*status = 1;
	if (set_pipe(node, master->env_list))
	{
		dup2(old_outfd, STDOUT_FILENO);
		dup2(old_infd, STDIN_FILENO);
		g_global.num_return_error = 1;
		return (NULL);
	}
	*status = execute_command(master, node, 0, NULL);
	if (dup2(old_outfd, STDOUT_FILENO) < 0)
		*status = 1;
	if (dup2(old_infd, STDIN_FILENO) < 0)
		*status = 1;
	if (close(old_infd) < 0 || close(old_outfd) < 0)
		print_error(NULL, 0, 1);
	return (node->next);
}

static void	execute_child(t_master *master, t_node *node)
{
	if (set_pipe(node, master->env_list))
		exit(EXIT_FAILURE);
	if (node->subshell)
		exit(executor(master, node->child));
	else
		exit(execute_command(master, node, 0, NULL));
}

static int	set_pipe(t_node	*node, t_env *env_list)
{
	int		fd_out;
	int		fd_in;
	bool	err;

	err = 0;
	fd_out = STDOUT_FILENO;
	fd_in = STDIN_FILENO;
	if (node->operator == TPIP)
		fd_out = node->fd[STDOUT_FILENO];
	if (is_post_op(node, TPIP))
		fd_in = node->prev->fd[STDIN_FILENO];
	if (dup2(fd_out, STDOUT_FILENO) < 0 || (dup2(fd_in, STDIN_FILENO) < 0))
		err = print_error(NULL, 0, 1);
	if (!err && node->redirects && prepare_redirect(node->redirects, env_list))
		err = 1;
	if (!err && node->operator == TPIP && close_pipe_fd(node->fd))
		err = print_error(NULL, 0, 1);
	if (!err && is_post_op(node, TPIP) && close_pipe_fd(node->prev->fd))
		err = print_error(NULL, 0, 1);
	if (err)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
