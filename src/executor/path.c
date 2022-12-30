/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 10:35:19 by aitoraudi         #+#    #+#             */
/*   Updated: 2022/12/29 10:35:22 by aitoraudi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

char	*get_path(char	*cmd)
{
	if (!ft_strncmp(cmd, "sleep", 7))
		return (ft_strjoin("/bin/", cmd));
	if (!ft_strncmp(cmd, "ls", 3))
		return (ft_strjoin("/bin/", cmd));
	if (!ft_strncmp(cmd, "echo", 7))
		return (ft_strjoin("/bin/", cmd));
	if (!ft_strncmp(cmd, "cat", 5))
		return (ft_strjoin("/bin/", cmd));
	if (!ft_strncmp(cmd, "grep", 5))
		return (ft_strjoin("/usr/bin/", cmd));
	if (!ft_strncmp(cmd, "sort", 5))
		return (ft_strjoin("/usr/bin/", cmd));
	if (!ft_strncmp(cmd, "wc", 5))
		return (ft_strjoin("/usr/bin/", cmd));
	if (!ft_strncmp(cmd, "awk", 5))
		return (ft_strjoin("/usr/bin/", cmd));
	return (cmd);
}
