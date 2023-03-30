/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:16:51 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/11 12:02:06 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	s_idx;
	size_t	d_idx;

	d_len = ft_strlen(dst);
	if (d_len < size)
	{
		s_idx = 0;
		d_idx = d_len;
		while (d_idx + 1 < size && src[s_idx])
			dst[d_idx++] = src[s_idx++];
		dst[d_idx] = 0;
		s_len = ft_strlen(src);
		return (d_len + s_len);
	}
	s_len = ft_strlen(src);
	return (size + s_len);
}
