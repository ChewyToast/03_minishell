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
