/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:41:37 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/23 18:59:08 by bmoll-pe         ###   ########.fr       */
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

int	get_export_values(t_node *node, char **name, char **value)// no estoy muy orgulloso de esto... nose como vamos a devolver los errores
{
	size_t	count;
	_Bool	err;

	count = 0;
	err = 0;
	if (!ft_isalpha(node->tokens[1][0]))
		err = 1;
	while (node->tokens[1][count])
	{
		if (!ft_isalpha(node->tokens[1][count]) && !ft_isdigit(node->tokens[1][count]))
			err = 1;
		if (err)
		{
			write(2, "ba.sh: export: `", 16);
			write(2, node->tokens[1], ft_strlen(node->tokens[1]));
			write(2, "\'m: not a valid identifier\n", 26);
			return (1);
		}
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