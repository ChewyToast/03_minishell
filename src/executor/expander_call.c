/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:57:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/06 13:58:40 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "defines.h"
#include "utils.h"
#include "env.h"
#include "expand_handler.h"

char	*token_and_expand(char *data_in, t_master *master_in, int reset,
			bool no_wilcard);

char	*init_tokenizer(char *data_in, t_master *master, bool wildcard)
{
	return (token_and_expand(data_in, master, 1, wildcard));
}

char	*get_next_token(bool wildcard)
{
	return (token_and_expand(NULL, NULL, 0, wildcard));
}
