/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:28:57 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/19 14:04:32 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_pass_black(const char *s)
{
	size_t	idx;

	idx = 0;
	while ((s[idx] >= 9 && s[idx] <= 13) || s[idx] == ' ')
		idx++;
	return (idx);
}

static int	ft_is_minus(const char *s, int *idx)
{
	int	is_minus;

	is_minus = 1;
	if (s[*idx] == '+' || s[*idx] == '-')
	{
		if (s[*idx] == '-')
			is_minus = -1;
		*idx = *idx + 1;
	}
	return (is_minus);
}

int	ft_atoi(const char *str)
{
	int			idx;
	int			is_m;
	long long	num;

	num = 0;
	idx = ft_pass_black(str);
	is_m = ft_is_minus(str, &idx);
	while (str[idx] && str[idx] >= '0' && str[idx] <= '9')
	{
		if (num && (num > num * 10 \
		|| num * 10 > num * 10 + (str[idx] - '0')))
		{
			if (is_m == 1)
				return (-1);
			else
				return (0);
		}
		num = num * 10 + (str[idx++] - '0');
	}
	return ((int)(num * is_m));
}
