/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:58:14 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/18 16:40:15 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(s1);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	while (len)
	{
		temp[len] = s1[len];
		len--;
	}
	temp[len] = s1[len];
	return (temp);
}
