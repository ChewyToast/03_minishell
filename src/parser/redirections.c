#include "defines.h"
#include "redirections.h"
#include "utils.h"

//	---- local headers
static bool	add_new_redirect(char *data, int type, int fd, t_node *node);
static int	get_redirect_fd(char *start, char *end);
static int 	extract_redirect(char **data, t_node *node, char *promt_init);

//	---- public
char	*extract_redirects_and_clean(char *data, t_node *node)
{
	char	*new_data;
	char	*full_data;
	bool	is_quoted;
	bool	is_dbl_quoted;
	bool	is_scaped;
	int		num_char_delete;

	full_data = data;
	new_data = ft_strdup("");
	if (new_data == NULL)
		return (NULL);
	while (*data)
	{
		if (*(data) == 92 && !is_quoted)
			is_scaped = 1;
		check_quotes(data, &is_quoted, &is_dbl_quoted);
		if (((*data) == '>' || (*data) == '<') && !is_quoted && !is_dbl_quoted && !is_scaped)
		{
			new_data = ft_chrjoin(new_data, ' ');
			num_char_delete = extract_redirect(&data, node, full_data);
			if (num_char_delete > 0)
			{
				new_data = ft_substr(new_data, 0, ft_strlen(new_data) - num_char_delete);
				new_data = ft_chrjoin(new_data, ' ');
			}
		}
		else
			new_data = ft_chrjoin(new_data, *(data++));
		is_scaped = 0;	
	}
	free (full_data);
	return (new_data);
}

//	---- local private
static int extract_redirect(char **data, t_node *node, char *promt_init)
{
	int		type;
	char	*redirect;
	char	*end;
	char	*start;
	int		num_char_del;
	int		fd;
	char	*symbol;
	
	symbol = *data;
	spaces_clean(data);
	type = get_type_redirect(data);
	if (!type)
		return (EXIT_FAILURE);
	start = get_redirect_start(symbol, promt_init);
	fd = get_redirect_fd(start, symbol);
	num_char_del = *data - start;
	end =  get_redirect_end(*data);
	spaces_clean(data);
	redirect = ft_substr(*data, 0, end - *data);
	*data = end;
	spaces_clean(data);
	add_new_redirect(redirect, type, fd, node);
	return (num_char_del);
}

static int	get_redirect_fd(char *start, char *end)
{
	char	*value;
	int		fd;

	value = ft_substr(start, 0 , end - start);
	while (ft_isdigit(*start) && end > start)
		start++;
	spaces_clean(&start);
	if (start != end)
		return (-1);
	fd = ft_atoi(value);
	free(value);
	return (fd);
}

static bool	add_new_redirect(char *data, int type, int fd, t_node *node)
{
	t_redirect	*new_redirect;
	t_redirect	*redirect_ini;

	new_redirect = malloc (sizeof (t_redirect));
	if (new_redirect == NULL)
		return (EXIT_FAILURE);
	new_redirect->type = type;
	new_redirect->data = ft_strdup(data);
	new_redirect->fd = fd;
	free (data);
	new_redirect->next = NULL;
	if (!node->redirects)
		node->redirects = new_redirect;
	else
	{
		redirect_ini = node->redirects;
		while (node->redirects->next)
			node->redirects = node->redirects->next;
		node->redirects->next = new_redirect;
		node->redirects = redirect_ini;
	}
	return (EXIT_SUCCESS);
}
