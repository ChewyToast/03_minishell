/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:31:31 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/17 18:12:18 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **env)
{
	t_master	master;
	char		*line;

	(void)argv;
	ft_bzero(&master, sizeof(t_master));
	if (argc != 1)
		return (0);
	master.env_list = env_parser(env);
	while (1)
	{
		line = readline("\033[38;5;143mba.sh $ \033[0;39m");
		if (!line)
			exit(1);
		if (line [0])
		{
			add_history(line);
			if (!ft_strncmp(line, "exit", 6))
				exit (0);
			if (parser(&master.node, line, 1))
				error("ba.sh: error parsing input\n", 1);
			////////////////// DEVELOP ///////////////////////////
			logtrace("🟢🟢🟢🟢🟢 NEW COMMAND 🟢🟢🟢🟢🟢", line, 0, 0);
			develop(&master.node);
			//////////////////////////////////////////////////////
			executor(master.node);
			master.node = free_tree(master.node);
		}
	}
	env_free_list(master.env_list);
	return (0);
}

void	develop(t_node **node)
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
