/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:27:39 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/11 12:01:20 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			idx;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	if (!n)
		return (0);
	idx = 0;
	s1_temp = (unsigned char *) s1;
	s2_temp = (unsigned char *) s2;
	while (idx < n)
	{
		if (s1_temp[idx] != s2_temp[idx] || idx == n - 1)
			return (s1_temp[idx] - s2_temp[idx]);
		idx++;
	}
	return (s1_temp[idx] - s2_temp[idx]);
}
