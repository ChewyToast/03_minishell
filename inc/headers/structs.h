/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:13:34 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/20 22:47:56 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define TUNDEF	-1
# define TEND	0
# define TSSH	1
# define TPIP	2
# define TCMD	3
# define TOR	4
# define TAND	5

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

# define DEF_COLOR	"\033[0;39m"
# define GRAY		"\033[0;90m"
# define RED		"\033[0;91m"
# define GREEN		"\033[0;92m"
# define YELLOW		"\033[0;93m"
# define BLUE		"\033[0;94m"
# define MAGENTA	"\033[0;95m"
# define CYAN 		"\033[0;96m"
# define WHITE		"\033[0;97m"
# define KNRM		"\x1B[0m"
# define KRED		"\x1B[31m"
# define KGRN		"\x1B[32m"
# define KYEL		"\x1B[33m"
# define KBLU		"\x1B[34m"
# define KMAG		"\x1B[35m"
# define KCYN		"\x1B[36m"
# define KWHT		"\x1B[37m"

# define U_ORANGE	"\033[48:5:208m"
# define U_WHITE	"\033[37;7:208m"
# define U_YELLOW	"\033[33;7:208m"
# define U_BLUE		"\033[34;7:208m"




typedef struct s_node		t_node;
typedef struct s_redirect	t_redirect;
typedef struct s_env		t_env;

/*
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
*/

struct s_node
{
	int			node_id;
	int			operator;
	char 		*data;
	char		**tokens;
	_Bool 		subshell;
	int			fd[2];
	t_node		*child;
	t_redirect	*redirects;
	pid_t		pid;
	int			return_value;
	t_node		*next;
	t_node		*prev;
};

struct s_redirect
{
	int			fd;
	int8_t		kind;
	t_redirect	*next;
};

struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
	t_env	*prev;	
};

#endif