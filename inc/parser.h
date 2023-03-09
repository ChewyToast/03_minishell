/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:43:27 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/09 13:27:47 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H\

bool	parser(t_node **list, char *parse_str, t_master *master);
_Bool	syntax_check(char **input);

#endif
