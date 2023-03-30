/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:11:48 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/13 15:42:04 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t_temp;

	t_temp = ft_lstnew(f(lst->content));
	if (!t_temp)
		return (0);
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&t_temp, ft_lstnew(f(lst->content)));
		if (!t_temp->next)
		{
			ft_lstclear(&t_temp, del);
			return (0);
		}
		lst = lst->next;
	}
	return (t_temp);
}
