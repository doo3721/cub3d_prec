/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:38:24 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/11 16:55:54 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

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

void	ft_putnbr_fd(int n, int fd)
{
	char	num[12];
	int		len;
	int		is_minus;

	len = ft_numlen(n);
	is_minus = 1;
	if (n < 0)
	{
		len++;
		is_minus = -1;
	}
	num[len--] = 0;
	while (len >= 0)
	{
		num[len--] = is_minus * (n % 10) + '0';
		n /= 10;
	}
	if (is_minus < 0)
		num[0] = '-';
	ft_putstr_fd(num, fd);
}
