/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:04:46 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/12 14:52:17 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "readline.h"
#include "history.h"
#include "executor.h"
#include "parser.h"
#include "utils.h"
#include "init.h"
#include "env.h"
#include "signals.h"
#include <fcntl.h>

static char	*read_user_input(t_master *master);
static void	parse_and_execute(t_master *master, char *line);

int	main(int argc, char **argv, char **env)
{
	t_master	master;
	char		*line;

	init_signals(NO_INTERACTIVE);
	init_program(&master, argc, argv, env);
	while (42)
	{
		line = read_user_input(&master);
		if (line[0])
			parse_and_execute(&master, line);
	}
	env_free_list(master.env_list);
	exit (g_global.num_return_error);
}

// system("leaks minishell");
static char	*read_user_input(t_master *master)
{
	char	*line;

	(void)master;
	init_signals(INTERACTIVE);
	line = readline("\033[38;5;143mba.sh $ \033[0;39m");
	init_signals(NO_INTERACTIVE);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		env_free_list(master->env_list);
		exit (g_global.num_return_error);
	}
	return (line);
}

static void	parse_and_execute(t_master *master, char *line)
{
	add_history(line);
	if (!syntax_check(&line))
	{
		if (line && parser(&(master->ast), line, master))
			print_error(ft_strdup("error parsing input"), 1, 1);
		free(line);
		if (master->print_tree)
			print_parse_tree(master->ast);
		g_global.num_return_error = executor(master, master->ast);
		master->ast = free_tree(master->ast);
	}
	else
	{
		if (g_global.is_ctrlc)
			g_global.is_ctrlc = 0;
		else
			g_global.num_return_error = 258;
		free(line);
	}
}
