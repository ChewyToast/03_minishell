/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:01:08 by test              #+#    #+#             */
/*   Updated: 2023/02/21 10:25:15 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

_Bool	prepare_redirect(int *fd, int8_t mode, t_redirect *redi)
{
	int	*last_fd;
	int	fd2;

	fd2 = 0;
	last_fd = &fd2;
	if (!redir)
		return (0);
	while (redi)
	{
		if (redi->type == mode)
		{
			if (*last_fd > 0)// Hemos encontrado otro, por lo que cerramos el anterior
				close(*last_fd);
			fd2 = prepare_fd(redi->data, redi->type);
		}
		else if (redi->type == mode + 2)
		redi = redi->next;
	}
}

static int	prepare_fd(char *data, int8_t type)
{
	if (type == RIN)
	{
		if (acces)
	}
}
