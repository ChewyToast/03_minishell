/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:49:55 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/10 12:54:50 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"
#include "signals.h"
#include "parser.h"
#include "executor.h"
#include <stdlib.h>

//	---- local headers
static void	init_master(t_master *master, char **env);
static void	add_bash_lvl(t_master *master, t_env *node);
static void	init_program_util(t_master *master, char **argv, char **env);
void		default_env(t_master *master);
void		bash_lvl_calculator(t_env *node,
				long long_value, unsigned int value);

//	---- public
void	init_program(t_master *master, int argc, char **argv, char **env)
{
	g_global.num_return_error = 0;
	ft_bzero(master, sizeof(t_master));
	master->inter_shell = 0;
	if (isatty(STDIN_FILENO))
		master->inter_shell = 1;
	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "-t", 3))
			master->print_tree = 1;
		else
			exit_program(ft_strdup(strerror(22)), 1, 1);
	}
	else if (argc == 3)
		init_program_util(master, argv, env);
	else if (argc > 3)
		exit_program(ft_strdup(strerror(22)), 1, 1);
	init_master(master, env);
}

//	---- private
static void	init_program_util(t_master *master, char **argv, char **env)
{
	int			size;
	char		*line;

	if (!ft_strncmp(argv[1], "-c", 3))
	{
		init_master(master, env);
		size = ft_strlen(argv[2]);
		if (ft_strrchr(argv[2], '\n'))
			size--;
		line = ft_substr(argv[2], 0, size);
		if (parser(&master->ast, line, master))
			print_error(ft_strdup("error parsing input"), 1, 1);
		if (master->print_tree)
			print_parse_tree(master->ast);
		executor(master, master->ast);
		master->ast = free_tree(master->ast);
		exit (g_global.num_return_error);
	}
	else
		exit_program(ft_strdup(strerror(22)), 1, 1);
}

static void	init_master(t_master *master, char **env)
{
	char	*check_is_master;

	master->path = NULL;
	g_global.is_master = false;
	if (*env)
	{
		master->env_list = env_parser(env);
		check_is_master = env_get_value(master->env_list, SH_WORD);
		if (!check_is_master)
		{
			env_new_value(&master->env_list, SH_WORD, "0");
			g_global.is_master = true;
		}
		else if (ft_atoi(check_is_master) == 1)
			env_set_value(&master->env_list, SH_WORD, "1");
		master->tild_value = env_get_value(master->env_list, "HOME");
		add_bash_lvl(master, env_search(master->env_list, "SHLVL"));
		if (!master->tild_value)
			master->tild_value = ft_substr("/Users/userID", 0, 14);
		if (!master->tild_value)
			exit_program(NULL, 0, 1);
		env_unset_node(master, "OLDPWD");
	}
	else
		default_env(master);
}

static void	add_bash_lvl(t_master *master, t_env *node)
{
	long long int	long_value;
	unsigned int	value;

	long_value = 0;
	value = 0;
	if (!node)
		env_new_value(&master->env_list, "SHLVL", "1");
	else if (node->value == NULL)
		env_set_value(&master->env_list, "SHLVL", "1");
	else
		bash_lvl_calculator(node, long_value, value);
}
