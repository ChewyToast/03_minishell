/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:47:14 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/26 18:15:57 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "readline.h"
#include <signal.h>

void	interactive_handler(int sig, siginfo_t *si, void *uap)
{
	(void) si;
	(void) uap;
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		global.num_return_error = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	no_interactive_handler(int sig, siginfo_t *si, void *uap)
{
	(void) si;
	(void) uap;
	if (sig == SIGINT)
	{
		if (global.is_master)
			write(1, "\n", 1);
		global.num_return_error = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (global.is_master)
			ft_putstr_fd("Quit: 3\n", 1);
		global.num_return_error = 131;
	}
	return ;
}

void	heredoc_handler(int sig, siginfo_t *si, void *uap)
{
	(void) si;
	(void) uap;
	if (sig == SIGINT)
	{
		global.is_ctrlC = 1;
		close(STDIN_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		write(STDOUT_FILENO, "\n", 1);
	}
	return ;
}

int	init_signals(int mode)
{
	struct sigaction	signal;

	signal.sa_flags = SA_RESTART;
	if (mode == INTERACTIVE)
		signal.sa_sigaction = interactive_handler;
	else if (mode == HERE_DOC)
		signal.sa_sigaction = heredoc_handler;
	else if (mode == NO_INTERACTIVE)
		signal.sa_sigaction = no_interactive_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	sigaction(SIGTERM, &signal, NULL);
	return (EXIT_SUCCESS);
}
