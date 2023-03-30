/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:07:36 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/18 16:40:59 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	idx;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_calloc(1, sizeof(char)));
	if (s_len - start > len)
		temp = (char *)malloc(sizeof(char) * (len + 1));
	else
		temp = (char *)malloc(sizeof(char) * (s_len - start + 1));
	if (!temp)
		return (0);
	idx = 0;
	while (idx < len && s[start])
		temp[idx++] = s[start++];
	temp[idx] = 0;
	return (temp);
}
