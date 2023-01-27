/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:41:37 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/27 19:38:35 by bmoll-pe         ###   ########.fr       */
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
	ssize_t	count;

	count = -1;
	while (node->tokens[1][++count] != '=' && !isscaped(&(node->tokens[1][count])))
		if (!ft_isalpha(node->tokens[1][count]) && !ft_isdigit(node->tokens[1][count]))
			break ;
	if (!ft_isalpha(node->tokens[1][0]) ||
		(node->tokens[1][count] && node->tokens[1][count] != '='
		&& !isscaped(&(node->tokens[1][count]))))
	{
		write(2, "ba.sh: export: `", 16);
		write(2, node->tokens[1], ft_strlen(node->tokens[1]));
		write(2, "\': not a valid identifier\n", 27);
		return (0);
	}
	if (!node->tokens[1][count])
		return (0);
	*name = ft_substr(node->tokens[1], 0, count);
	if (!name)
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	if (node->tokens[1][++count])
		*value = ft_substr(node->tokens[1], count, 0xffffff);
	else
		*value = NULL;
	if (node->tokens[1][count] && !(*value))
		error("ba.sh: Error trying to allocate memory\n", 1);// ERROR!!!!
	return (0);
}

