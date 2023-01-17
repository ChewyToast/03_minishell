/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/17 23:36:30 by bmoll-pe         ###   ########.fr       */
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

int	exec_cd(t_node	*node)
{
	ft_printf("CD!!!\n");
	// if (node->tokens[0] && !node->tokens[1])
	// 	return (0);
	if (chdir(NULL) == -1)
	// if (chdir(node->tokens[1]) == -1)
	{
		write(2, "ba.sh: ", 7);
		perror(NULL);
		exit (1);
	}
	else
		(void)node;// ACTUALIZAR LAST PWD DEL ENV
	return (0);
}