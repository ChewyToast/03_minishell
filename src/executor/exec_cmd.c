#include "bmlib.h"
#include "structs.h"
#include "minishell.h"

char	**expander(char **tokens, t_master *master);

void	execute_command(t_master *master, t_node *node)
{
	//Ejecutamos comando
	// 1.- Expandimos wilcards y dolars
	// 2.- Ejecutamos en función de si es builtin o execve
	
	node->tokens = expander(node->tokens, master);
	if (is_builtin (node))
		execute_builtins(master, node);
	else
	{
		execve(check_cmd(master, node), node->tokens, env_to_array(master->env_list));
		error("ba.sh: execve error\n", 1);
	}
}

char	**expander(char **tokens, t_master *master)
{
	char	**expanded_tokens;
	
	(void) master;
	expanded_tokens = expand_wildcard(tokens);
	//expanded_tokens = expand_dollars(tokens);
	return (expanded_tokens);
}

int	execute_builtins(t_master *master, t_node *node)
{
	(void)master;
	// Ejecutamos el builting correspondiente

	// Si ha sido llamado desde el padre, tendremos que salir con return ya que un exit nos cerraría el parograma principal
	if (!is_in_pipe(node) && is_builtin(node))
		return (0);
	else
		exit(0);
}