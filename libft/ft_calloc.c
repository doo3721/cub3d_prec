/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:41:29 by doohkim           #+#    #+#             */
/*   Updated: 2022/07/21 14:22:30 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;

	if (size && count * size / size != count)
		return (0);
	temp = malloc(size * count);
	if (!temp)
		return (0);
	ft_memset(temp, 0, size * count);
	return (temp);
}
