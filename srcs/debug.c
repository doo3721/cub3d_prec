/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:35:51 by doohkim           #+#    #+#             */
/*   Updated: 2023/03/21 16:36:13 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_casting.h"

void	print_map(t_game_struct *g_obj)
{
	int	h_idx;
	int	w_idx;

	h_idx = 0;
	while (h_idx < MAP_HEIGHT)
	{
		w_idx = 0;
		while (w_idx < MAP_WIDTH)
		{
			ft_putchar_fd(g_obj->map_arr[h_idx][w_idx] + '0', 1);
			w_idx++;
		}
		ft_putchar_fd('\n', 1);
		h_idx++;
	}
}