/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/18 16:31:37 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <limits.h>

int	exec_pwd(void)
{
	char	*buff;

	ft_printf("PWD!!!\n");
	buff = ft_calloc(PATH_MAX + 1, 1);
	if (!getcwd(buff, PATH_MAX))
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	if (ft_printf("%s\n", buff) == -1)
		return (1);// ERROR!!!!
	return (0);
}

int	exec_cd(t_master *master, t_node	*node)
{
	bool	error;

	master->last_ret = 1;
	error = false;
	ft_printf("CD!!!\n");
	if (node->tokens[0] && !node->tokens[1])
	{
		if (chdir(master->tild_value) == -1)
			error = true;
	}
	else if (chdir(node->tokens[1]) == -1)
			error = true;
	if (error)
	{
		write(2, "ba.sh: ", 7);
		perror(NULL);
		exit (1);
	}
	(void)node;// ACTUALIZAR LAST PWD DEL ENV
	master->last_ret = 0;
	return (0);
}