/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:31:31 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/13 02:51:22 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "bmlib.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	init_master(t_master *master, char **env);

int	main(int argc, char **argv, char **env)
{
	t_master	master;
	char		*line;

	(void)argv;
	ft_bzero(&master, sizeof(t_master));
	if (argc != 1)
		return (0);
	init_master(&master, env);
	while (1)
	{
		line = readline("\033[38;5;143mba.sh $ \033[0;39m");
		if (!line)
		{
			// system("leaks minishell");
			exit(1);
		}
		if (line [0])
		{
			add_history(line);
			if (!syntax_check(line))
			{
				if (parser(&master.node, line, 1))
					error("ba.sh: error parsing input\n", 1);
				develop(&master.node);
				executor(&master, master.node);
				master.node = free_tree(master.node);
			}
			else
			{
				free(line);
				write(1, "ba.sh: syntax error near unexpected token\n", 42);
				// falta que se quede en la variable exit code el numero 258
			}
		}
	}
	env_free_list(master.env_list);
	return (0);
}

static void	init_master(t_master *master, char **env)
{
	t_env	*tmp;

	master->env_list = env_parser(env);
	tmp = master->env_list;
	ft_printf("tmp: ->%s<-\n", tmp->name);
	while (tmp && ft_strncmp(tmp->name, "PATH", 4))
	{
		ft_printf("tmp: ->%s=%s<-\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	if (tmp)
		master->path = ft_split(tmp->value, ';');
	else
		master->path = NULL;
}

void	develop(t_node **node)// no entiendo esta funcion
{
	print_parse_tree(*node);
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
		free_split(node->tokens);
		free (node);
		node = temp;
	}
	return (NULL);
}

void	error(char *error, int num_error)
{
	perror(error);
	//ft_putstr_fd(2, error);
	exit(num_error);
}

// void	error(t_master *master, char *error, int num_error)
// {
// 	if (master)
// 	{
// 		free_tree(master->node);
// 		master->node = NULL;
// 		env_free_list(master->env_list);
// 	}
// 	printf("%s\n", error);
// 	exit (num_error);
// }
