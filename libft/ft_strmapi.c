/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 11:55:14 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/19 13:52:26 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*f_str;
	size_t	idx;
	size_t	len;

	len = ft_strlen(s);
	f_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!f_str)
		return (0);
	idx = 0;
	while (idx < len)
	{
		f_str[idx] = f(idx, s[idx]);
		idx++;
	}
	f_str[idx] = 0;
	return (f_str);
}
