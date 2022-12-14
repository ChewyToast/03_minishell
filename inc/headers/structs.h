/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:13:34 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/14 16:50:31 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define TUNDEF	-1
# define TCOLON	1
# define TOR	2
# define TAND	3
# define TPIP	4
# define TCMD	5

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_node		t_node;
typedef struct s_redirect	t_redirect;

struct s_node
{
	int			node_id;
	int8_t		type;
	char		*start;
	char		*end;
	t_node		*top;
	t_node		*right;
	t_node		*left;
	t_redirect	*redirect;
};

struct s_redirect
{
	int			fd;
	int8_t		kind;
	t_redirect	*next;
};

#endif