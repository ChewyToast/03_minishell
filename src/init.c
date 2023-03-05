/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:49:55 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/05 22:31:27 by aitoraudica      ###   ########.fr       */
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
		
	ft_bzero(master, sizeof(t_master));
	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "-t", 3))
			master->print_tree = 1;
		else
			exit_program(ft_strdup("ba.sh: incorrect parameter\n"), 1);	
	}
	else if (argc == 3)
	{
		if(!ft_strncmp(argv[1], "-c", 3))
		{
			size = ft_strlen(argv[2]);
			if (ft_strrchr(argv[2], '\n'))
				size--;
			line = ft_substr(argv[2], 0, size);
			if (parser(&master->node, line, 1))
					print_error("ba.sh: error parsing input\n", 1);
			if (master->print_tree)
				print_parse_tree(master->node);
			executor(master, master->node);
			master->node = free_tree(master->node);
			exit_program (NULL, 0);
		}
		else
			exit_program(ft_strdup("ba.sh: incorrect parameter\n"), 1);
	}
	else if (argc > 3)
		exit_program(ft_strdup("ba.sh: incorrect arguments\n"), 1);
	init_master(master, env);
	init_signals(NO_INTERACTIVE);

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
			exit_program (ft_strdup("ba.sh: memeory error\n"), 1);// error de memoria exit el que sea
	}
	else
	{
		ft_printf("no hay env!\n");
		default_env(master);
		master->tild_value = ft_substr("/Users/UserID", 0, 14);// en este, hay que hacer una funcion para calcular el valor
	}	
}


static void	add_bash_lvl(t_master *master, t_env *node)
{
	int	value;

	if (!node)
		return ;
	value = ft_atoi(node->value);
	value += 1;
	master->shlv = value;
	free(node->value);
	node->value = ft_itoa(value);
	if (node->value)
		return ;
	free_tree(master->node);
	env_free_list(master->env_list);
	write(2, "ba.sh: memory error\n", 20);
}

static void	default_env(t_master *master)
{
	char	*buff;

	buff = ft_calloc(PATH_MAX + 1, 1);
	if (env_new_value(&master->env_list, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."))
		exit (1);// ERROR!!
	if (env_new_value(&master->env_list->next, "SHLVL", "1"))
		exit (1);// ERROR!!
	if (!getcwd(buff, PATH_MAX))
		exit_program(ft_strdup("ba.sh: Error trying to allocate memory"), 1);// ERROR!!!!
	if (env_new_value(&master->env_list->next->next, "PWD", buff))
		exit (1);// ERROR!!
	if (env_new_value(&master->env_list->next->next->next, "_", "/usr/bin/env"))
		exit (1);// ERROR!!
	free(buff);
}
