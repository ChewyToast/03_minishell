/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:01:08 by test              #+#    #+#             */
/*   Updated: 2023/04/12 14:18:31 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "readline.h"
#include "signals.h"
#include <fcntl.h>
#include "redirects.h"
#include "executor.h"
#include "defines.h"
#include "env.h"

//	---- local headers
static bool	prepare_fd(int *fd, char *data, int8_t type);
static bool	prepare_iter(t_redirect *redi, t_env *env_list,
				int *tmp_fd, int16_t *group);

//	---- public
bool	prepare_redirect(t_redirect *redi, t_env *env_list)
{
	int			tmp_fd;
	int			error;
	int16_t		*group;
	// int16_t		group[OPEN_MAX];

	error = 0;
	tmp_fd = 0;
	group = ft_calloc(sizeof(int16_t), OPEN_MAX);
	// ft_memset(group, '\0', OPEN_MAX);
	while (redi && !error)
	{
		error = prepare_iter(redi, env_list, &tmp_fd, group);
		tmp_fd = 0;
		redi = redi->next;
	}
	while (tmp_fd++ < OPEN_MAX)
		if (group[tmp_fd] > 2)
			close(group[tmp_fd]);
	return (error);
}

//	---- private
static bool	prepare_iter(t_redirect *redi, t_env *env_list,
				int *tmp_fd, int16_t *group)
{
	if (redi->type == RDOC && own_here_doc(tmp_fd, redi, env_list))
		return (print_error(NULL, 0, 1));
	if (redi->type != RDOC && prepare_fd(tmp_fd, redi->data, redi->type))
		return (print_error(ft_strdup(redi->data), 0, 1));
	if (*tmp_fd > 0 && (redi->type != RDOC || is_last_here(redi, tmp_fd)))
	{
		if (dup2(*tmp_fd, redi->fd) < 0)
			return (print_error(NULL, 0, 1));
		if (group[redi->fd] > 2 && close(group[redi->fd]) < 0)
			return (print_error(NULL, 0, 1));
		group[redi->fd] = *tmp_fd;
	}
	return (0);
}

static bool	prepare_fd(int *fd, char *data, int8_t type)
{
	if (type == RIN)
		*fd = open(data, O_RDONLY);
	else if (type == ROUT)
		*fd = open(data, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (type == RADD)
		*fd = open(data, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*fd < 0)
		return (1);
	return (0);
}
