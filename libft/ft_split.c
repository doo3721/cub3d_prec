/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 09:43:48 by doohkim           #+#    #+#             */
/*   Updated: 2023/03/21 16:28:49 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_arrcount(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*ft_splitdup(const char *s, char c)
{
	char	*temp;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	temp[len--] = 0;
	while (len)
	{
		temp[len] = s[len];
		len--;
	}
	temp[len] = s[len];
	return (temp);
}

void	ft_splits_clear(char **splits)
{
	int	idx;

	if (!splits)
		return ;
	idx = 0;
	while (splits[idx])
		free(splits[idx++]);
	free(splits);
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	size_t	count;
	size_t	s_idx;

	count = ft_arrcount(s, c);
	splits = (char **)malloc(sizeof(char *) * (count + 1));
	if (!splits)
		return (0);
	s_idx = 0;
	while (s_idx < count)
	{
		while (*s == c)
			s++;
		splits[s_idx] = ft_splitdup(s, c);
		if (!splits[s_idx])
		{
			ft_splits_clear(splits);
			return (0);
		}
		while (*s && *s != c)
			s++;
		s_idx++;
	}
	splits[s_idx] = 0;
	return (splits);
}
