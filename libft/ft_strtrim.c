/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:47:19 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/18 16:40:43 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	idx;
	char	*temp;

	start = 0;
	end = ft_strlen(s1);
	if (end)
		end--;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
		return (ft_calloc(1, sizeof(char)));
	temp = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!temp)
		return (0);
	idx = 0;
	while (start <= end)
		temp[idx++] = s1[start++];
	temp[idx] = 0;
	return (temp);
}
