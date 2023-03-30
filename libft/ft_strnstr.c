/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohee kim <doo3721@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:28:19 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/12 10:43:55 by doohee kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hay_idx;
	size_t	temp_idx;
	size_t	n_idx;

	hay_idx = 0;
	if (!ft_strncmp(needle, "", 1))
		return ((char *) haystack);
	while (hay_idx < len && haystack[hay_idx])
	{
		n_idx = 0;
		temp_idx = hay_idx;
		while (haystack[temp_idx] && needle[n_idx]
			&& haystack[temp_idx] == needle[n_idx]
			&& temp_idx < len)
		{
			temp_idx++;
			n_idx++;
		}
		if (!needle[n_idx])
			return ((char *) &haystack[hay_idx]);
		if (!haystack[temp_idx])
			return (NULL);
		hay_idx++;
	}
	return (NULL);
}
