/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:41:37 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/20 13:58:11 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"
#include <limits.h>
/*
HAY QUE VER CON LOS ERRORES, HACEMOS EXIT? RETURN?
*/
char	*get_current_pwd(void)
{
	char	*pwd;
	char	*tmp;

	pwd = ft_calloc(PATH_MAX + 1, 1);
	if (!getcwd(pwd, PATH_MAX))
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	tmp = ft_substr(pwd, 0, 0xffffffff);
	free (pwd);
	pwd = NULL;
	if (!tmp)
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	return (tmp);
}

int	get_export_values(t_node *node, char **name, char **value)
{
	size_t	count;

	count = 0;
	while (node->tokens[1][count])
	{
		if (node->tokens[1][count] == '=')// nose como saber si esta escapado...
			break ;
		count++;
	}
	if (!node->tokens[1][count])
		return (0);
	*name = ft_substr(node->tokens[1], 0, count);
	if (!name)
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	if (node->tokens[1][count] && node->tokens[1][count + 1])
		*value = ft_substr(node->tokens[1], count + 1, 0xffffff);
	else
		*value = NULL;
	if (node->tokens[1][count] && node->tokens[1][count + 1] && !(*value))
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	return (0);
}