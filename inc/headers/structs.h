/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:13:34 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/13 23:27:45 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define DCOLON 1
# define DOR 2
# define DAND 3

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_master		t_master;
typedef struct s_redirect	t_redirect;
typedef struct s_command	t_command;
typedef struct s_bracket	t_bracket;

struct s_master
{
	char	**env;
	int		exit_code;
};

struct s_redirect
{
	int			fd;
	int8_t		kind;
	t_redirect	*next;
};

struct s_command
{
	char		**cmds;
	char		*start;
	char		*end;
	int8_t		link;
	t_command	*next;
};

struct s_bracket
{
	char		*start;
	char		*end;
	t_redirect	*redirect;
	t_command	*command;
	t_bracket	*next;
};

#endif