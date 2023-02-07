#include "structs.h"
#include "minishell.h"
#include "bmlib.h"


int	exec_echo(t_node *node)
{
	bool	no_new_line;
	int		i;

	no_new_line = 0;
	i = 1;
	while (node->tokens[i] && !ft_strncmp(node->tokens[i], "-n", 2))
	{
		no_new_line = 1;
		i++;
	}
	while(node->tokens[i])
	{
		ft_putstr_fd(node->tokens[i++], 1);
		// HABRIA QUE PROTEGER LOS WRITESS ALGO ASI QUIZAS?
		// if (node->tokens[i] && write(1, " ", 1) < 1)
		//		return (1);// ERROR !!
		if (node->tokens[i])
			write(1, " ", 1);
	}
	if (!no_new_line)
		write(1, "\n", 1);
		// if (write(1, "\n", 1) < 0)
		// 		return (1);// ERROR !!
	return (EXIT_SUCCESS);
}