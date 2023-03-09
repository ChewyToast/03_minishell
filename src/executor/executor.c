/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/09 13:58:07 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "exec_utils.h"
#include "exec_cmd.h"
#include "signals.h"
#include "redirects.h"

//	---- local headers
static	t_node	*execute_pipe(t_master *master, t_node *node, int *status);
static	void execute_child(t_master *master, t_node *node);
static	int	set_pipe(t_node	*node, t_env *env_list);
static	int	waiting_pipe(t_node *node);
static void	free_fdman(t_fdmanage **fdman);

//	---- public
int	executor(t_master *master, t_node *node)
{
	int		status;

	while (node)
	{
		node = execute_pipe(master, node, &status);
		if (is_post_op(node, TAND))
		{
			if (status > 0)
				node = get_next(node, TOR);
		}
		else if (is_post_op(node, TOR))
		{
			if (!status)
				node = get_next(node, TAND);
		}
	}
	return (status);
}

//	---- private
static	t_node	*execute_pipe(t_master *master, t_node *node, int *status)
{
	t_node	*node_init;

	if (!node)
		return (NULL);
	if (!is_in_pipe(node) && !node->subshell && is_builtin(master, node))
	{
		int old_infd = dup(STDIN_FILENO);
		int old_outfd = dup(STDOUT_FILENO);
		if (set_pipe(node, master->env_list))
			{ft_printf("ERROR DE ALGUNA MOVIDA\n"); return (NULL);}//ERROR
		*status = execute_command(master, node);
		global.num_return_error = *status;
		if (dup2(old_outfd, STDOUT_FILENO) < 0)
			return (NULL);
		if (dup2(old_infd, STDIN_FILENO) < 0)
			return (NULL);
		return (node->next);
	}
	node_init = node;

	while (node)
	{
		if (node->operator == TPIP)
			pipe(node->fd);
		node->pid = fork();
		if (node->pid < 0)
			exit (EXIT_FAILURE);// ERROR!!!!!!!!
		if (node->pid == 0)
			execute_child(master, node);
		if (node->prev && node->prev->operator == TPIP)
			close_pipe_fd(node->prev->fd);
		if (node->operator != TPIP)
			break ;
		node = node->next;
	}
	*status = waiting_pipe(node_init);
	global.num_return_error = *status;
	if (node)
		return (node->next);
	else
		return (NULL);
}

static	void	execute_child(t_master *master, t_node *node)
{
	if (set_pipe(node, master->env_list))
		exit(EXIT_FAILURE);
	if (node->subshell)
		exit(executor(master, node->child));
	else
		exit (execute_command(master, node));
}

static	int	set_pipe(t_node	*node, t_env *env_list)
{
	t_fdmanage	*fdman;
	int			fd_out;
	int			fd_in;

	fdman = NULL;
	fd_out = STDOUT_FILENO;// Preparamos siempre fd de salida
	fd_in = STDIN_FILENO;//	  y de entrada

	if (node->operator == TPIP)// Si va a un pipe, cambiamos a ese fd
		fd_out = node->fd[STDOUT_FILENO];

	if (is_post_op(node, TPIP))// lo mismo con la entrada, si viene de uno
		fd_in = node->prev->fd[STDIN_FILENO];

	if (dup2(fd_out, STDOUT_FILENO) < 0 || (dup2(fd_in, STDIN_FILENO) < 0))// redireccionamos la salida
		return (EXIT_FAILURE);
	if (node->redirects)// si hay mas redirecciones las hacemos
	{
		if (add_fdman(&fdman, 0, fd_in) || add_fdman(&fdman, 1, fd_out))
			return (EXIT_FAILURE);
		if (prepare_redirect(&fdman, node->redirects, env_list))
			return (EXIT_FAILURE);
		free_fdman(&fdman);
	}

	if (node->operator == TPIP && close_pipe_fd(node->fd))
		return (EXIT_FAILURE);
	if (is_post_op(node, TPIP) && close_pipe_fd(node->prev->fd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


int	waiting_pipe(t_node *node)
{
	int	status;

	while (node)
	{
		if (node->pid > 0)
			waitpid(node->pid, &status, 0);
		if (WIFEXITED(status))
			node->status = WEXITSTATUS(status);
		if (node->operator != TPIP)
			break ;
		node = node->next;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

static void	free_fdman(t_fdmanage **fdman)
{
	t_fdmanage	*tmp;

	tmp = (*fdman)->next;
	while (*fdman)
	{
		free(*fdman);
		*fdman = tmp;
		if (*fdman)
			tmp = (*fdman)->next;
		return ;
	}
}
