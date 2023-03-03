/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/03 15:15:10 by aitoraudica      ###   ########.fr       */
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
#include <fcntl.h>

int	main(int argc, char **argv, char **env)
{
	t_master	master;
	char		*line;
	int			size;
	
	init_program (&master, argc, argv, env);
	while (1)
	{
		if (master.arg_line_mode)
		{	
			size = ft_strlen(argv[2]);
			if (ft_strrchr(argv[2], '\n'))
				size--;
			line = ft_substr(argv[2], 0, size);
			if (parser(&master.node, line, 1))
					print_error("ba.sh: error parsing input\n", 1);
			if (master.print_tree)
				print_parse_tree(master.node);
			executor(&master, master.node);
			master.node = free_tree(master.node);
			exit_program (NULL, 0);
		}
		line = readline("\033[38;5;143mba.sh $ \033[0;39m");
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				exit_program(ft_strdup("exit"), 1);
			exit_program(NULL, 0);
		}
		if (line [0])
		{
			add_history(line);
			if (!syntax_check(&line))
			{
				if (parser(&master.node, line, 1))
					print_error("ba.sh: error parsing input\n", 1);
				if (master.print_tree)
					print_parse_tree(master.node);
				executor(&master, master.node);
				master.node = free_tree(master.node);
			}
			else
			{
				free(line);
				ft_printf("ba.sh: syntax error\n");
				// falta que se quede en la variable exit code el numero 258
			}
		}
	}
	//int ret = master.last_ret;
	env_free_list(master.env_list);
	exit_program (NULL, global.num_return_error);
}