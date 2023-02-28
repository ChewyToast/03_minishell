#include "defines.h"

//	---- local headers
static void	init_master(t_master *master, char **env)

//	---- public
void	init_program(t_master *master, int argc, char **argv, char **env)
{
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
			master->arg_line_mode = 1;
		else
			exit_program(ft_strdup("ba.sh: incorrect parameter\n"), 1);
	}
	else if (argc > 3)
		exit_program(ft_strdup("ba.sh: incorrect arguments\n"), 1);
	init_master(master, env);
	init_signals(INTERACTIVE);
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
			is_master = true;
		}		
		else if (ft_atoi(check_is_master) == 1)
		{
			is_master = false;
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
