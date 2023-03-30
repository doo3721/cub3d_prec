/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:21:21 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/13 11:48:36 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*t_temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	t_temp = *lst;
	while (t_temp->next)
		t_temp = t_temp->next;
	t_temp->next = new;
}
