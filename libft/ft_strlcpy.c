/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:12:36 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/11 17:01:01 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	if (size)
	{
		len = 0;
		while (len + 1 < size && src[len])
		{
			dst[len] = src[len];
			len++;
		}
		dst[len] = 0;
	}
	return (ft_strlen(src));
}
