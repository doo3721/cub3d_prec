/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:26:54 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/11 12:01:17 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			idx;

	temp = (unsigned char *) s;
	idx = 0;
	while (idx < n)
	{
		if (temp[idx] == (unsigned char) c)
			return (&temp[idx]);
		idx++;
	}
	return (NULL);
}
