#ifndef EXPANDER_H
# define EXPANDER_H

#define LIM_DOLLAR 1
#define LIM_WILDCARD 2
#define LIM_INIT 3

typedef struct s_tokener	t_tokener;

struct s_tokener
{
	char		*data;
	char		*end_expansion;
	t_master	*master;
	bool		is_quoted;
	bool		is_dbl_quoted;
	int			exp_mode;
	char		*original_promt;
	char		*full_data;
	bool		return_token;
};

char	*expand_wildcard(t_tokener *tk, char *new_data);
int		quotes_sub_handler(t_tokener *tk, char type);

#endif