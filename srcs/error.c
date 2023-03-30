/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:41:39 by doohkim           #+#    #+#             */
/*   Updated: 2023/03/21 15:49:22 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_casting.h"

static void	ft_clear_game_struct(t_game_struct *g_obj)
{
	(void)g_obj;
}

int	ft_error(char *str, t_game_struct *g_obj)
{
	ft_clear_game_struct(g_obj);
	printf("Error\n%s\n", str);
	return (EXIT_FAILURE);
}
