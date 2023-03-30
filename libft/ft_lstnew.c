/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:48:32 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/18 16:39:37 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*t_new;

	t_new = (t_list *)malloc(sizeof(t_list));
	if (!t_new)
		return (0);
	t_new->content = content;
	t_new->next = 0;
	return (t_new);
}
