
#include "defines.h"
#include <signal.h>

void	interactive_handler(int sig, siginfo_t *si, void *uap)
{
	(void) si;
	(void) uap;
	
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		if (write(1, "\n", 1) < 0)
			return ;// ERROR!!
		rl_on_new_line();
		rl_redisplay();
		num_return_error = 1;
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
		if (is_master)
			write(1, "\n", 1);
		num_return_error = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (is_master)
			ft_putstr_fd("Quit: 3\n", 1);
		num_return_error = 131;
	}
	return ;
}

 
int	init_signals(int mode)
{
	struct sigaction	signal;

	signal.sa_flags = SA_RESTART;
	if (mode == INTERACTIVE)
		signal.sa_sigaction = interactive_handler;
	else if (mode == NO_INTERACTIVE)
		signal.sa_sigaction = no_interactive_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	sigaction(SIGTERM, &signal, NULL);
	return (EXIT_SUCCESS);
}