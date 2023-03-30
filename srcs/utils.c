/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:50:52 by doohkim           #+#    #+#             */
/*   Updated: 2023/03/21 15:51:02 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_casting.h"

int	ft_strrcmp(const char *str, const char *target)
{
	int	str_idx;
	int	target_idx;

	if (!str || !target)
		return (-1);
	str_idx = ft_strlen(str);
	target_idx = ft_strlen(target);
	while (str_idx > 0 && target_idx > 0)
	{
		if (str[str_idx] != target[target_idx])
			return ((unsigned char) str[str_idx] \
					- (unsigned char) target[target_idx]);
		str_idx--;
		target_idx--;
	}
	if (!str_idx)
		return (-1);
	return ((unsigned char) str[str_idx] - (unsigned char) target[target_idx]);
}
