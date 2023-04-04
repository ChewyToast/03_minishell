/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:49:01 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/04 13:52:13 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	print_error(char *data, bool print_msg, int err_num)
{
	char	*errormsg;

	g_global.num_return_error = err_num;
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

// system("leaks minishell");
void	exit_program(char *data, bool print_msg, int err_num)
{
	print_error(data, print_msg, err_num);
	exit(err_num);
}
