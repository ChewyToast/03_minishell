#include "structs.h"
#include "minishell.h"
#include "bmlib.h"


int	exec_echo(t_node *node)
{
	bool	no_new_line;
	int		i;

	ft_printf("ECHO!!!\n");
	no_new_line = 0;
	i = 0;
	if (!ft_strncmp(node->tokens[1], "-n", 2))
	{
		no_new_line = 1;
		i++;
	}
	while(node->tokens[i])
	{
		ft_putstr_fd(node->tokens[i++], 1);
		write(1, " ", 1);
	}
	if (!no_new_line)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}