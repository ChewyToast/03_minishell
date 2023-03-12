/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:49:55 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/12 20:00:48 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "env.h"
#include "signals.h"
#include "parser.h"
#include "executor.h"

//	---- local headers
static void	init_master(t_master *master, char **env);
static void	add_bash_lvl(t_master *master, t_env *node);
static void	default_env(t_master *master);

//	---- public
void	init_program(t_master *master, int argc, char **argv, char **env)
{
	int			size;
	char		*line;	

	global.num_return_error = 0;
	ft_bzero(master, sizeof(t_master));
	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "-t", 3))
			master->print_tree = 1;
		else
			exit_program(ft_strdup(strerror(22)), 1, 1);
	}
	else if (argc == 3)
	{
		if(!ft_strncmp(argv[1], "-c", 3))
		{
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
			exit (global.num_return_error);
		}
		else
			exit_program(ft_strdup(strerror(22)), 1, 1);
	}
	else if (argc > 3)
			exit_program(ft_strdup(strerror(22)), 1, 1);
	init_master(master, env);
}

//	---- private
static void	init_master(t_master *master, char **env)
{
	master->path = NULL;
	char	*check_is_master;
	
	if (*env)
	{
		master->env_list = env_parser(env);
		check_is_master = env_get_value(master->env_list, SH_WORD);
		if (!check_is_master)
		{
			env_new_value(&master->env_list, SH_WORD, "0");
			global.is_master = true;
		}		
		else if (ft_atoi(check_is_master) == 1)
		{
			global.is_master = false;
			env_set_value(&master->env_list, SH_WORD, "1");
		}		
		master->tild_value = env_get_value(master->env_list, "HOME");
		add_bash_lvl(master, env_search(master->env_list, "SHLVL"));
		if (!master->tild_value)
			master->tild_value = ft_substr("/Users/UserID", 0, 14);// en este caso y... (linea 134)
		if (!master->tild_value)
			exit_program(NULL, 0, 1);
	}
	else
	{
		default_env(master);
		master->tild_value = ft_substr("/Users/UserID", 0, 14);// en este, hay que hacer una funcion para calcular el valor @to_do
	}	
}


static void	add_bash_lvl(t_master *master, t_env *node)
{
	long long value;

	if (!node)
		env_new_value(&master->env_list, "SHLVL", "1");
	else if (node->value == NULL)
		env_set_value(&master->env_list, "SHLVL", "1");
	else
	{
		value = ft_atoi_long_long(node->value);
		value += 1;
		value = (unsigned int) value;
		free(node->value);
		if (value > 1000)
		{
			printf("ba.sh: warning: shell level (%lld) too high, resetting to 1\n", value);
			value = 1;
		}
		if (value == 1000)
			node->value	= NULL;
		else
			node->value = ft_itoa(value);
	}
}

static void	default_env(t_master *master)
{
	char	*buff;

	buff = ft_calloc(PATH_MAX + 1, 1);
	if (env_new_value(&master->env_list, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."))
			exit_program(NULL, 0, 1);
	if (env_new_value(&master->env_list->next, "SHLVL", "1"))
			exit_program(NULL, 0, 1);
	if (!getcwd(buff, PATH_MAX))
			exit_program(NULL, 0, 1);
	if (env_new_value(&master->env_list->next->next, "PWD", buff))
			exit_program(NULL, 0, 1);
	if (env_new_value(&master->env_list->next->next->next, "_", "/usr/bin/env"))
			exit_program(NULL, 0, 1);
	free(buff);
}
