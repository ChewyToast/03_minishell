/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:06:51 by test              #+#    #+#             */
/*   Updated: 2023/01/29 12:25:19 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"
#include "bmlib.h"

//
	size_t	parts_counter(char *input);
	_Bool	main_loop(char *input, char **tokens);
	size_t	clean_spaces(char *input);
	char	*quotes_case(char **input);
	char	*spaces_case(char **input);
	int8_t	fill(char ***tokens, char *tmp, size_t spaces);
	int8_t	join_last(char **tokens, char *tmp);
	void	clean_scpaes(char *token);
//

char	*get_token(char **data)
{
	// ft_printf("\nLE LLEGA:\n ->%s<-\n", *data);
	size_t	count;
	char	*token;
	char	quote;

	count = 0;
	quote = 0;
	token = ft_calloc(1, 1);
	if (!(data) || !(*data) || !(**data))
		return (NULL);// ERROR!!!
	if (!token)
		return (NULL);// ERROR!!!
	while(ft_isspace(**data))
		*data += 1;
	if (**data == '\0')
		return (NULL);
	while(data[0][count] && (!ft_isspace(data[0][count]) || isscaped(&(data[0][count]))))
	{
		if ((isquote(&data[0][count], 34) || isquote(&data[0][count], 39)))
		{
			quote = data[0][count];
			count++;
			while (data[0][count] && (data[0][count] != quote || isscaped(&(data[0][count]))))
			{
				token = ft_chrjoin(token, data[0][count]);
				if (!token)
					return (NULL);// ERROR!!!
				count++;
			}
			if (data[0][count]) 
				count++;
		}
		else
		{
			token = ft_chrjoin(token, data[0][count]);
			if (!token)
				return (NULL);// ERROR!!!
			count++;;
		}
	}
	*data += count;
	if (**data)
		while(ft_isspace(**data))
			*data += 1;
	// ft_printf("TOKEN:\n ->%s<-\n", token);
	return (token);
}

char	**tokenizer(char *input)
{
	char	**tokens;

	// if (clean_wd(input))
	// 	return (NULL);
	tokens = ft_calloc(sizeof(char *), parts_counter(input));
	if (!tokens)
		return (NULL);
	if (main_loop(input, tokens))
	{
		while (*tokens)
			free(*(tokens++));
		free(tokens);
		return (NULL);
	}
	return (tokens);
}

size_t	parts_counter(char *input)
{
	size_t	count;
	char	delim;

	count = 0;
	while (*input)
	{
		input += clean_spaces(input);
		if (input && (isquote(input, 34) || isquote(input, 39)))
		{
			delim = *input;
			input++;
			while ((*input) && !isquote(input, delim))
				input++;
			if (*input)
				input++;
			count++;
		}
		else if (input)
		{
			while (*input && (!isquote(input, 34) && !isquote(input, 39)
					&& (!ft_isspace(*input) || isscaped(input))))
				input++;
			count++;
		}
	}
	return (count + 1);
}

_Bool	main_loop(char *input, char **tokens)
{
	char	*tmp;
	size_t	spaces;

	spaces = 0;
	while (*input)
	{
		spaces = clean_spaces(input);
		input += spaces;
		if (!*input)
			break ;
		if (input && (isquote(input, 34) || isquote(input, 39)))
			tmp = quotes_case(&input);
		else if (input)
			tmp = spaces_case(&input);
		if (!tmp)
			return (1);
		if (input && fill(&tokens, tmp, spaces))
			return (1);
		tmp = NULL;
	}
	return (0);
}

size_t	clean_spaces(char *input)
{
	size_t	rtrn;

	rtrn = 0;
	while (ft_isspace(input[rtrn]) || isscaped(&input[rtrn]))
		rtrn++;
	return (rtrn);
}

char	*quotes_case(char **input)
{
	char	*new;
	char	delim;
	size_t	size;

	size = 0;
	delim = **input;
	(*input) += 1;
	while ((*input)[size] && !isquote(&(*input)[size], delim))
		size++;
	new = ft_calloc(sizeof(char), size + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, (*input), size);
	(*input) += size + 1;
	return (new);
}

char	*spaces_case(char **input)
{
	char	*new;
	size_t	size;

	size = 0;
	while ((*input)[size] && (!isquote(&(*input)[size], 34)
		&& !isquote(&(*input)[size], 39)
		&& (!ft_isspace((*input)[size])
		|| isscaped(&(*input)[size]))))
		size++;
	new = ft_calloc(sizeof(char), size + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, (*input), size);
	*input += size;
	return (new);
}

int8_t	fill(char ***tokens, char *tmp, size_t spaces)
{
	int8_t	rtrn;

	rtrn = 0;
	if (!(**tokens))
	{
		**tokens = tmp;
		clean_scpaes(**tokens);
		return (rtrn);
	}
	if (spaces)
	{
		*tokens += 1;
		**tokens = tmp;
		clean_scpaes(**tokens);
	}
	else
		return (join_last(*tokens, tmp));
	return (rtrn);
}

int8_t	join_last(char **tokens, char *tmp)
{
	char	*new;
	size_t	tkn_size;
	size_t	tmp_size;

	tkn_size = ft_strlen(*tokens);
	tmp_size = ft_strlen(tmp);
	new = ft_calloc(sizeof(char), tkn_size + tmp_size + 1);
	if (!new)
		return (1);
	ft_memcpy(new, *tokens, tkn_size);
	ft_memcpy(new + tkn_size, tmp, tmp_size);
	free(*tokens);
	free(tmp);
	*tokens = new;
	new = NULL;
	tmp = NULL;
	return (0);
}

void	clean_scpaes(char *token)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[j] == 92)
			j++;
		token[i] = token[j];
		i++;
		j++;
	}
}
