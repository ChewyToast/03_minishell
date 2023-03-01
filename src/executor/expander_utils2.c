#include "expander.h"
#include "wildcard.h"
#include "utils.h"

int	quotes_sub_handler(t_tokener *tk, char type)
{
	if (type == 39)
		tk->is_quoted = !tk->is_quoted;
	if (type == 34)
		tk->is_dbl_quoted = !tk->is_dbl_quoted;
	if ((type == 39 && !tk->is_quoted) || (type == 34 && !tk->is_dbl_quoted))
	{
		tk->data++;
		return (0);
	}
	if (is_isolated_quotes(tk->data, type))
	{
		if (type == 39)
			tk->is_quoted = !tk->is_quoted;
		if (type == 34)
			tk->is_dbl_quoted = !tk->is_dbl_quoted;
		while (*tk->data == type)
			tk->data++;
		if (*tk->data)
			tk->data++;
		return (1);
	}
	tk->data++;
	return (0);
}

char	*expand_wildcard(t_tokener *tk, char *new_data)
{
	int		pos;
	char	*expanded;
	char	*word;
	char	*word_init;
	int		to_delete;
	char	*temp;

	word_init = get_word_init(tk->data, tk->full_data, LIM_INIT);
	to_delete = tk->data - word_init;
	temp = ft_substr(new_data, 0, ft_strlen(new_data) - to_delete);
	free(new_data);
	new_data = temp;
	tk->data = get_word_init(tk->data, tk->full_data, 0);
	pos = get_word_end(tk->data, LIM_WILDCARD) - tk->data;
	word = ft_substr(tk->data, 0, pos);
	expanded = expand_str_wildcard(word);
	free (word);
	tk->data = str_pro_join(tk->data + pos, expanded, 0);
	tk->exp_mode = 2;
	tk->end_expansion = tk->data + ft_strlen(expanded);
	free(expanded);
	free(tk->original_promt);
	tk->original_promt = tk->data;
	return (new_data);
}