/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:01:08 by test              #+#    #+#             */
/*   Updated: 2023/02/21 18:29:37 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <fcntl.h>
#include <errno.h>

static int	prepare_fd(int *fd, char *data, int8_t type);

_Bool	prepare_redirect(int *fd, int8_t mode, t_redirect *redi)
{
	int	fd2;

	fd2 = 0;
	if (!redi)
		return (0);
	while (redi)
	{
		if (redi->type == mode || redi->type == mode + 2)
			if (fd2 > 0)// Hemos encontrado otro, por lo que cerramos el anterior
				close(fd2);	
		if (redi->type == mode)
		{
			if (prepare_fd(&fd2, redi->data, redi->type) < 0)
				return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
		}
		else if (redi->type == mode + 2)
		{
			if (redi->type == RADD)
			{
				if (prepare_fd(&fd2, redi->data, redi->type) < 0)
					return (print_error(ft_strjoin("ba.sh: ", strerror(errno)), 1));
			}
			else
				ft_printf("HEREDOC\n");
		}
		redi = redi->next;
	}
	*fd = fd2;
	return (0);
}

static int	prepare_fd(int *fd, char *data, int8_t type)
{
	if (type == RIN)
	{
		if (access(data, F_OK))
			return (print_error(ft_strjoin("ba.sh: ", ft_strjoin(data, ": No such a file or directory\n")), 0));
		if (access(data, R_OK))
			return (print_error(ft_strjoin("ba.sh: ", ft_strjoin(data, ": Permision denied\n")), 0));
		*fd = open(data, O_RDONLY);
	}
	else if (type == ROUT)
	{
		if (!access(data, F_OK))
			if (access(data, W_OK))
				return (print_error(ft_strjoin("ba.sh: ", ft_strjoin(data, ": Permision denied\n")), 0));
		*fd = open(data, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	else if (type == RADD)
	{
		if (!access(data, F_OK))
			if (access(data, W_OK))
				return (print_error(ft_strjoin("ba.sh: ", ft_strjoin(data, ": Permision denied\n")), 0));
		*fd = open(data, O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
	return (*fd);
}
