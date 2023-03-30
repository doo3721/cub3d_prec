/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:25:20 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/15 16:09:48 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			idx;
	unsigned char	*temp;

	idx = 0;
	temp = (unsigned char *) s;
	while (temp[idx])
	{
		if (temp[idx] == (unsigned char) c)
			return ((char *) &temp[idx]);
		idx++;
	}
	if (temp[idx] == (unsigned char) c)
		return ((char *) &temp[idx]);
	return (0);
}
