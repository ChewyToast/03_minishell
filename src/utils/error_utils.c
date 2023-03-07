/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:49:01 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/03 15:17:29 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

int	print_error(char *error, int num_error)
{
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
	free(error);
	return (num_error);
}

void 	exit_program(char *msg_error, int num_error)
{
	// Free master
	if (msg_error)
		print_error(msg_error, num_error);
	// system("leaks minishell");
	if (num_error < 0)
		exit(global.num_return_error);
	exit (num_error);
}
