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