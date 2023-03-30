/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 11:03:25 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/18 16:39:11 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numlen(int n)
{
	size_t	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	size_t	len;
	int		is_minus;

	len = ft_numlen(n);
	is_minus = 1;
	if (n < 0)
	{
		len++;
		is_minus = -1;
	}
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len--] = 0;
	while (len)
	{
		num[len--] = is_minus * (n % 10) + '0';
		n /= 10;
	}
	num[len] = is_minus * (n % 10) + '0';
	if (is_minus < 0)
		num[0] = '-';
	return (num);
}
