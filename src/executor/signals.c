/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:47:14 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/13 18:40:54 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "readline.h"
#include "utils.h"
#include <signal.h>

void	interactive_handler(int sig, siginfo_t *si, void *uap)
{
	(void) si;
	(void) uap;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_global.is_ctrlc = 1;
		g_global.num_return_error = 1;
	}
	return ;
}

void	no_interactive_handler(int sig, siginfo_t *si, void *uap)
{
	(void) si;
	(void) uap;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_global.is_ctrlc = 1;
		g_global.num_return_error = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (g_global.is_master)
			ft_putstr_fd("Quit: 3\n", 1);
		g_global.num_return_error = 131;
	}
	return ;
}

void	heredoc_handler(int sig, siginfo_t *si, void *uap)
{
	(void) si;
	(void) uap;
	if (sig == SIGINT)
	{
		g_global.is_ctrlc = 1;
		close(STDIN_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		write(STDOUT_FILENO, "\n", 1);
	}
	return ;
}

void	do_sigign(int signum)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(signum, &signal, NULL) < 0)
		exit_program(NULL, 1, 1);
}

int	init_signals(int mode)
{
	struct sigaction	signal;

	signal.sa_flags = SA_RESTART;
	if (mode == INTERACTIVE)
		signal.sa_sigaction = interactive_handler;
	else if (mode == NO_INTERACTIVE)
		signal.sa_sigaction = no_interactive_handler;
	else if (mode == HERE_DOC)
		signal.sa_sigaction = heredoc_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	return (EXIT_SUCCESS);
}
