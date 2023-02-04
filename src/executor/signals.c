#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include "readline.h"
#include "history.h"
#include <signal.h>

void	interactive_handler(int sig, siginfo_t *si, void *uap)
{
	(void) si;
	(void) uap;
	
	if (sig == SIGINT)
	{
		//write(1, "\b", 1);
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		num_return_error = 1;
	}
	else if (sig == SIGQUIT)
	{
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
		num_return_error = 130;
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: 3\n", 1);
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
	else
		signal.sa_sigaction = no_interactive_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	sigaction(SIGTERM, &signal, NULL);
	return (EXIT_SUCCESS);
}