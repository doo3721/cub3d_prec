/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:26:08 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/15 16:22:25 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			idx;
	unsigned char	*temp;

	idx = ft_strlen(s);
	temp = (unsigned char *) s;
	while (1)
	{
		if (temp[idx] == (unsigned char) c)
			return ((char *) &temp[idx]);
		if (!idx)
			break ;
		idx--;
	}
	return (NULL);
}
