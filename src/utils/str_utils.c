/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:49:13 by ailopez-          #+#    #+#             */
/*   Updated: 2023/04/06 13:55:37 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

char	*ft_strjoin_free(char	*str1, char	*str2)
{
	char	*new_str;

	new_str = ft_strjoin(str1, str2);
	free (str1);
	free (str2);
	return (new_str);
}

char	*str_pro_join(char *str1, char *str2, int pos)
{
	int		new_size;
	char	*new_str;
	char	*ret_str;

	new_size = ft_strlen(str1) + ft_strlen(str2);
	new_str = malloc (sizeof (char) * (new_size + 1));
	if (new_str == NULL)
		return (NULL);
	ret_str = new_str;
	while (*str1 && pos && pos--)
		*(new_str++) = *(str1++);
	while (*str2)
		*(new_str++) = *(str2++);
	while (*str1)
		*(new_str++) = *(str1++);
	*new_str = '\0';
	return (ret_str);
}

char	*ft_chrjoin(char *str, char c)
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
	while (*str)
		*(new_str++) = *(str++);
	*(new_str++) = c;
	*(new_str) = '\0';
	free(free_ptr);
	return (return_ptr);
}

int	spaces_clean_back(char **data, char *str_ini)
{
	char	*data_in;

	data_in = *data;
	while (ft_isspace(**data) && *data > str_ini)
		(*data)--;
	if (ft_isspace(**data))
		(*data)--;
	return (data_in - *data);
}

int	pre_spaces_clean(char **data)
{
	char	*data_in;

	data_in = *data;
	while (ft_isspace(**data) && **data != '\0')
		(*data)++;
	if (*data > data_in)
		(*data)--;
	return (*data - data_in);
}
