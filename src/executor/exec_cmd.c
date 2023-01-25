/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:52:11 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/01/25 14:35:23 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "structs.h"
#include "minishell.h"
#include <limits.h>

bool 	is_word_limit(char c);
char	*get_word_end(char *data);
char	*get_word_init(char *data, char *data_min);
char	*ft_strjoin_free(char	*str1, char	*str2);
char	*ft_chrjoin(char	*str, char	c);
char	*expand_data(char *data, t_master *master);
int		get_end_redirects (char *data);

int	execute_command(t_master *master, t_node *node)
{
	char	*expanded_data;

	expanded_data = expand_data(node->data, master);
	// ------------/ DEBUG
	printf("%s >> Expanded data :: %s [%s]\n", U_ORANGE, DEF_COLOR, expanded_data);
	node->tokens = tokenizer(expanded_data);
	free (expanded_data);
	// ------------/ DEBUG	
	print_parse_tree(node);	
	if (is_builtin (node))
		return (execute_builtins(master, node));
	execve(check_cmd(master, node), node->tokens, env_to_array(master->env_list));
	error("ba.sh: execve error\n", 1);
	return (EXIT_FAILURE);
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

char	*expand_data(char *data, t_master *master)
{
	char	*new_data;
	char	*expanded;
	char	*word;
	bool	is_quoted;
	bool	is_dbl_quoted;
	int		pos;
	char	*full_data;
	char	*word_init;
	int		to_delete;
	char	*temp;
	char	*redirect_data;
	
	(void)temp;
	(void)redirect_data;
	full_data = data;
	new_data = ft_strdup("");
	while (*data)
	{
		if ((*data) == 39)
		{
			is_quoted = !is_quoted;
			new_data = ft_chrjoin(new_data, *(data++));
		}
		else if ((*data) == 34)
		{
			is_dbl_quoted = !is_dbl_quoted;
			new_data = ft_chrjoin(new_data, *(data++));
		}
		// else if (((*data) == '>' || (*data) == '<') && !is_quoted && !is_dbl_quoted)
		// {
		// 	pos = get_end_redirects(data);
		// 	redirect_data = ft_substr(data, 0, pos);
		// 	data = data + pos;
		// }
		else if ((*data) == '$' && !is_quoted)
		{
			pos = get_word_end(data) - data;
			word = ft_substr(data, 1, pos - 1);
			expanded = ft_strdup(env_get_value(master->env_list, word));
			free (word);
			new_data = ft_strjoin_free (new_data, expanded);
			data = data + pos;
		}		
		else if ((*data) == '*' && !is_quoted)
		{
			word_init = get_word_init(data, full_data);
			to_delete = data - word_init;
			temp = ft_substr(new_data, 0, ft_strlen(new_data) - to_delete);
			free (new_data);
			new_data = temp;
			data = get_word_init(data, full_data);
			pos = get_word_end(data) - data;
			word = ft_substr(data, 0, pos);
			expanded = expand_str_wildcard(word);
			new_data = ft_strjoin_free (new_data, expanded);
			data = data + pos;
		}
		else if ((*data) == '~')
		{
			expanded = env_get_value(master->env_list, "HOME");
			if (expanded == NULL)
				expanded = ft_strdup(master->tild_value);
			new_data = ft_strjoin_free (new_data, expanded);
			data++;
		}
		else
			new_data = ft_chrjoin(new_data, *(data++));
	}
	free (full_data);
	return (new_data);
}

int	get_end_redirects (char *data)
{

	(void) data;
	return (0);

}

bool is_word_limit(char c)
{
	if (c == '>')
		return (true);
	if (c == '<')
		return (true);
	if (c == ' ')
		return (true);
	if (c == 39)
		return (true);
	if (c == 34)
		return (true);			
	if (c == '\0')
		return (true);
	return (false);
}

char	*get_word_end(char *data)
{
	while (*data && !is_word_limit(*data))
		data++;
	return (data);
}

char	*get_word_init(char *data, char *data_min)
{
	while (*data && !is_word_limit(*data) && data > data_min)
		data--;
	return (++data);
}


