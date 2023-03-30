/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:21:42 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/11 13:59:25 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				idx;
	unsigned char		*temp;
	const unsigned char	*src_temp;

	if (dest == NULL && src == NULL)
		return (NULL);
	temp = dest;
	src_temp = src;
	idx = 0;
	while (idx < n)
	{
		temp[idx] = (unsigned char) src_temp[idx];
		idx++;
	}
	return (dest);
}
