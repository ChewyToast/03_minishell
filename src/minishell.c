/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:31:31 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/26 20:08:12 by aitoraudica      ###   ########.fr       */
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
		line = readline("\n\033[38;5;143mba.sh $ \033[0;39m");
		if (!line)
			exit(1);
		if (line [0])
		{
			if (parser(&master.node, line, 1))
				error(&master, "ba.sh: error parsing input\n", 1);
			//add_history(line);
			//logtrace("🟢🟢🟢🟢🟢 NEW COMMAND 🟢🟢🟢🟢🟢", line, 0, 0);	
			////////////////// DEVELOP ///////////////////////////
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
	if (!ft_strncmp((*node)->data, "exit", 6))
		exit (0);
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
		free (node);
		free_split(node->tokens);
		node = temp;
	}
	return (NULL);
}

void	error(t_master *master, char *error, int num_error)
{
	if (master)
	{
		free_tree(master->node);
		master->node = NULL;
		env_free_list(master->env_list);
	}
	printf("%s\n", error);
	exit (num_error);
}
