/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:22:47 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/15 17:04:35 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_forward_move(void *dest, const void *src, size_t n)
{
	size_t				idx;
	unsigned char		*temp;
	const unsigned char	*src_temp;

	temp = dest;
	src_temp = src;
	idx = 0;
	while (idx < n)
	{
		temp[idx] = src_temp[idx];
		idx++;
	}
	return (temp);
}

static void	*ft_back_move(void *dest, const void *src, size_t n)
{
	size_t				idx;
	unsigned char		*temp;
	const unsigned char	*src_temp;

	temp = dest;
	if (!n)
		return (temp);
	src_temp = src;
	idx = n;
	if (idx)
		idx--;
	while (idx)
	{
		temp[idx] = src_temp[idx];
		idx--;
	}
	temp[idx] = src_temp[idx];
	return (temp);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest <= src)
		return (ft_forward_move(dest, src, n));
	else
		return (ft_back_move(dest, src, n));
}
