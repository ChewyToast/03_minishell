/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:43:27 by ailopez-          #+#    #+#             */
/*   Updated: 2023/03/12 20:01:01 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H\

bool	parser(t_node **list, char *parse_str, t_master *master);
_Bool	syntax_check(char **input);

#endif
