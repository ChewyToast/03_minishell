/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/08 20:20:48 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include "posixstat.h"
#include "readline.h"
#include "history.h"
#include <fcntl.h>


static void	init_master(t_master *master, char **env);
static void	init_program(t_master *master, int argc, char **argv, char **env);
char	*str_pro_join(char *str1, char *str2, int pos);
char	**make_scape_table(char *str);

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
					error("ba.sh: error parsing input\n", 1);
			if (master.print_tree)
				print_parse_tree(master.node);
			executor(&master, master.node);
			master.node = free_tree(master.node);
			exit_program (NULL, 0);
		}
		line = readline("\033[38;5;143mba.sh $ \033[0;39m");
		if (!line)
		{
			exit_program("exit\n", 1);
			// system("leaks minishell");
		}
		if (line [0])
		{
			add_history(line);
			if (!syntax_check(line))
			{
				if (parser(&master.node, line, 1))
					error("ba.sh: error parsing input\n", 1);
				if (master.print_tree)
					print_parse_tree(master.node);
				executor(&master, master.node);
				master.node = free_tree(master.node);
			}
			else
			{
				free(line);
				error("ba.sh: syntax error near unexpected token\n", 42);
				// falta que se quede en la variable exit code el numero 258
			}
		}
	}
	env_free_list(master.env_list);
	exit_program (NULL, 0);
}

static void	init_program(t_master *master, int argc, char **argv, char **env)
{
	ft_bzero(master, sizeof(t_master));
	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "-t", 3))
			master->print_tree = 1;
		else
			exit_program("ba.sh: incorrect parameter\n", 1);	
	}
	else if (argc == 3)
	{
		if(!ft_strncmp(argv[1], "-c", 3))
			master->arg_line_mode = 1;
		else
			exit_program("ba.sh: incorrect parameter\n", 1);
	}
	else if (argc > 3)
		exit_program("ba.sh: incorrect arguments\n", 1);
	init_master(master, env);
	init_signals(INTERACTIVE);
}

static void	init_master(t_master *master, char **env)
{
	master->path = NULL;
	if (*env)
	{
		master->env_list = env_parser(env);
		master->tild_value = env_get_value(master->env_list, "HOME");
		add_bash_lvl(master, env_search(master->env_list, "SHLVL"));
		if (!master->tild_value)
			master->tild_value = ft_substr("/Users/UserID", 0, 14);// en este caso y...
		if (!master->tild_value)
			exit_program ("ba.sh: memeory error\n", 1);// error de memoria exit el que sea
	}
	else
	{
		ft_printf("no hay env!\n");
		default_env(master);
		master->tild_value = ft_substr("/Users/UserID", 0, 14);// en este, hay que hacer una funcion para calcular el valor
	}
}

t_node	*free_tree(t_node *node)
{
	t_node	*temp;

	while (node)
	{
		if (node->child)
			free_tree(node->child);
		temp = node->next;
		free (node->data);
		if (node->tokens)
			free_split(node->tokens);
		free (node);
		node = temp;
	}
	return (NULL);
}

void	error(char *error, int num_error)
{
	(void)  num_error;
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}

void 	exit_program(char *msg_error, int num_error)
{
	// Free master
	if (msg_error)
		error(msg_error, num_error);
	if (num_error < 0)
		exit(num_return_error);
	exit (num_error);
}
