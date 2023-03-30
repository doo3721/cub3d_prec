/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:24:27 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/18 16:40:26 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	s1_len;
	size_t	s2_len;
	size_t	idx;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!temp)
		return (0);
	idx = 0;
	while (idx < s1_len)
	{
		temp[idx] = s1[idx];
		idx++;
	}
	idx = s1_len;
	while (idx < s1_len + s2_len)
	{
		temp[idx] = s2[idx - s1_len];
		idx++;
	}
	temp[idx] = 0;
	return (temp);
}
