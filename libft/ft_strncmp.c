/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:17:18 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/15 15:46:03 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	idx = 0;
	if (!n)
		return (0);
	while (s1[idx] || s2[idx])
	{
		if ((s1[idx] != s2[idx]) || (idx + 1 == n))
			return ((unsigned char) s1[idx] - (unsigned char) s2[idx]);
		idx++;
	}
	return ((unsigned char) s1[idx] - (unsigned char) s2[idx]);
}
