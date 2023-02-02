/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:47:32 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/10/07 22:23:45 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

// LIBRARY FOR READ()
# include <unistd.h>

// LIBRARY FOR MALLOC()
# include <stdlib.h>

// LIBRARY FOR OPEN_MAX MACROS
//# include <limits.h>

char	*get_next_line(const int fd);

char	*copy_line(char *buff);
size_t	check_nl(const char *str);
char	*ft_readd(const int fd, char *saved_buff);
char	*cut_static(char *total_buff);

char	*ft_strjoinn(char *total_buff, char *tmp, size_t totalln, size_t tmpln);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlenne(const char *s);
char	*ft_substrr(char *total_buff, size_t start, size_t len);

# define BUFFER_SIZE 1
# define OPEN_MAX 1023

#endif
