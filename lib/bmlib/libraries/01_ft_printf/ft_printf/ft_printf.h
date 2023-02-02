/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:26:12 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/06/12 11:46:58 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <strings.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

int		ft_printf(const char *inp_str, ...);
ssize_t	ft_read(const char *str, va_list args);

ssize_t	ft_ptoa(unsigned long long int n);
ssize_t	ft_itoa(int n);
ssize_t	ft_uitoa(unsigned int n);
ssize_t	ft_10to16(unsigned int n, int mode);

ssize_t	ft_putchar(char c);
ssize_t	ft_putstr(const char *str);
int		ft_strlen(const char *s);

#endif
