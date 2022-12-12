/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:09:34 by bruno             #+#    #+#             */
/*   Updated: 2022/12/12 15:43:58 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//compile linux: gcc src/parsing/parsing.c -lreadline

// typedef struct s_parse
// {
// 	char	type;
// 	char	*start;
// 	char	*end;
// 	t_parse	*next;
// }	t_parse;

// _Bool	parsing(char *input, t_parse **strc);

int	main(void)
{
	t_parse	*strc;
	char	*input;

	strc = NULL;
	input = readline("ba.sh $ ");
	printf("->%s<-\n", input);
	if (parsing(argv[1], &strc))
		return (printf("error parsing\n"));
	// print_result(&strc);
	// free_all(&strc);
	exit (0);
}

// _Bool	parsing(char *input, t_parse **strc)
// {
// 	*strc = malloc(sizeof(t_parse));
// 	if (!*strc)
// 		return (1);
// 	while (*input)
// 	{
// 		while(*input && ft_isspace(*input))
// 			input++;
// 		if (*input && )
// 	}
// }

// _Bool	is_block()

// char	ft_isspace(int argv)
// {
// 	if (argv == 32
// 		|| argv == '\n'
// 		|| argv == '\t'
// 		|| argv == '\v'
// 		|| argv == '\f'
// 		|| argv == '\r')
// 		return (argv);
// 	return (0);
// }

//(echo 1 || (echo 2 | cat -e)) || echo end
//echo 1 || (echo 2 | cat -e) || echo end
//(ecdho 1 || (echo 2 | cat -e)) || echo end
//(ecdho 1 || (echfdo 2 | cat -e)) || echo end
//ecdho 1 || (echfdo 2 | echo hola) || echo end
//(ecdho 1 || (echfdo 2 | echo hola)) || echo end
//(ecdho 1 || (echfdo 2 | echo hola)) || echo end 2> oup
//((ecdho 1 || (echfdo 2 | echo hola)) || echo end) 2> oup
//< a.out edscho hola || cat -e
//< a.out (edscho hola || cat -e)
//echo hola | cat < a.out | grep hola
//echo holaecho | cat << hola | grep hola