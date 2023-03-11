/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:49:01 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/11 00:37:31 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	print_error(char *data, bool print_msg, int err_num)
{
	char *errormsg;

	write(1,"@", 1);
	global.num_return_error = err_num;
	errormsg = strerror(errno);
	if (data && print_msg)
	{
		write(2, "ba.sh: ", 7);
		write(2, data, ft_strlen(data));
	}
	else
	{
		write(2, "ba.sh: ", 7);
		if (data)
		{
			write(2, data, ft_strlen(data));
			write(2, ": ", 2);
		}
		write(2, errormsg, ft_strlen(errormsg));
	}
	write(2, "\n", 1);
	if (data)
		free(data);
	return (1);
}

void 	exit_program(char *data, bool print_msg, int err_num)
{
	print_error(data, print_msg, err_num);
	// system("leaks minishell");
	exit(err_num);
}
