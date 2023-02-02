/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 02:42:01 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/05/27 22:07:50 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*flst;
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst)
		return (0);
	flst = NULL;
	while (lst)
	{
		tmp2 = f(lst->content);
		tmp = ft_lstnew(tmp2);
		if (!(tmp))
		{
			del(tmp2);
			ft_lstclear(&flst, del);
			return (0);
		}
		ft_lstadd_back(&flst, tmp);
		lst = lst->next;
	}
	return (flst);
}
