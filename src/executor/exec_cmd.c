/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/20 10:25:11 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

char	**expander(char **tokens, t_master *master);


char	*ft_strjoin_free(char	*str1, char	*str2)
{
	char	*new_str;

	new_str = ft_strjoin(str1, str2);
	free (str1);
	free (str2);
	return (new_str);
}

char	*ft_chrjoin(char	*str, char	c)
{
	char	*new_str;
	char	*return_ptr;
	char	*free_ptr;
	int		len;

	len = ft_strlen(str);
	new_str = malloc((len + 2) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	return_ptr = new_str;
	free_ptr = str;
	while(*str)
		*(new_str++) = *(str++);
	*(new_str++) = c;
	*(new_str) = '\0';
	free(free_ptr);
	return (return_ptr);
}

char	*expand_quotes(char **data)
{
	char	*new_str;
	
	new_str = ft_strdup("");
	(*data)++;
	while ((**data) != 39)
		new_str = (ft_chrjoin(new_str, *(*data)++));
	(*data)++;
	return (new_str);
}

char	*expand_dbl_quotes(char **data, t_master *master)
{
	(void)data;
	(void)master;
	return (*data);
}

char	*expand_data(char *data, t_master *master)
{
	char	*new_data;
	char	*expanded;
	char	*to_free;
	
	to_free = data;
	new_data = ft_strdup("");
	while (*data)
	{
		if ((*data) == 92)
		{
			new_data = ft_chrjoin(new_data, *(++data));
			data++;
		}
		else if ((*data) == 39 || (*data) == 34)
		{
			if ((*data) == 39)
				expanded = expand_quotes(&data);
			else
				expanded = expand_dbl_quotes(&data, master);
			new_data = ft_strjoin_free(new_data, expanded);
		}
		else if ((*data) == '>' || (*data) == '<')
		{
			// Extraer redirecciones
		}
		else if ((*data) == '$')
		{
			// Extraer env
		}		
		else if ((*data) == '*')
		{
			// Extraer wildcard
		}
		else if ((*data) == '~')
		{
			// Extraer home
		}
		// else if ((*data) == ' ' && *(data + 1) == ' ')
		// {
		// 	data++;
		// }
		else
			new_data = ft_chrjoin(new_data, *(data++));
	}
	free(to_free);
	return (new_data);
}


//Ejecutamos comando
// 1.- Expandimos wilcards y dolars
// 2.- Tokenizacion
// 3.- Ejecutamos en función de si es builtin o execve

int	execute_command(t_master *master, t_node *node)
{
	//write(1, "X", 1);
	char	*expanded_data;
	//node->tokens = expander(node->tokens, master);
	expanded_data = expand_data(node->data, master);
	printf("expanded data [%s]\n", expanded_data);
	//node->tokens = tokenizer(expanded_data);
	node->tokens = ft_split(expanded_data, ' ');
	print_parse_tree(node);	
	if (is_builtin (node))
		return (execute_builtins(master, node));
	execve(check_cmd(master, node), node->tokens, env_to_array(master->env_list));
	error("ba.sh: execve error\n", 1);
	return (EXIT_FAILURE);
}

char	**expander(char **tokens, t_master *master)
{
	char	**expanded_tokens;

	(void) master;
	expanded_tokens = expand_wildcard(tokens);
	return (expanded_tokens);
}

int	execute_builtins(t_master *master, t_node *node)
{
	(void)master;
	// print_env(master->env_list);
	// ft_printf("---------> HOME >%s<\n", getenv("HOME"));
	if (!ft_strncmp(node->tokens[0], "pwd", 4))
		return (exec_pwd());
	if (!ft_strncmp(node->tokens[0], "cd", 3))
		return (exec_cd(master, node));
	return (1);
}