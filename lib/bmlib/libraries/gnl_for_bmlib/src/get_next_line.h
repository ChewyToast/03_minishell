/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:47:32 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/15 11:47:33 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// LIBRARY FOR READ()
# include <unistd.h>

// LIBRARY FOR MALLOC()
# include <stdlib.h>

/*~~~~~~~~~~~~~~~~GET_NEXT_LINE~~~~~~~~~~~~~~~~*/
char	*get_next_line(int fd);
char	*fd_readd(int fd, char *total_buff);
char	*take_line(char *total_buff);
char	*cut_static(char *total_buff);

/*~~~~~~~~~~~~~~~~GET_NEXT_LINE_UTILS~~~~~~~~~~~~~~~~*/
char	*ft_strjoinn(char *total_buff, char *tmp);
char	*ft_substrr(const char *total_buff, unsigned int start, size_t len);
char	*check_char(const char *str, int c);
size_t	ft_strlenne(const char *str);
char	*nter_malloc(size_t nbytes, size_t size);

# define BUFFER_SIZE 1

#endif
