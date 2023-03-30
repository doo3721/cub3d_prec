/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:16:55 by doohkim           #+#    #+#             */
/*   Updated: 2023/03/30 16:34:43 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_H
# define RAY_CASTING_H
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx_mms/mlx.h"

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define WIN_WIDTH 640
# define WIN_HEIGHT 480

typedef enum e_event_type
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_event_type;

typedef enum e_keycode
{
	A_KEY = 0,
	D_KEY = 2,
	W_KEY = 13,
	S_KEY = 1,
	LEFT_KEY = 123,
	RIGHT_KEY = 124,
	SPACE_KEY = 49,
	ESC_KEY = 53
}	t_keycode;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_frame
{
	double	time;
	double	old_time;
	double	move_speed;
	double	rot_speed;
}	t_frame;

typedef struct s_image
{
	void			*img_ptr;
	char			*img_data;
	int				pixel_x;
	int				pixel_y;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}	t_image;

typedef struct s_game_struct
{
	char		map_arr[MAP_HEIGHT][MAP_WIDTH];
	void		*mlx_ptr;
	void		*win_ptr;
	int			map_width;
	int			map_height;
	t_player	p_obj;
	t_frame		f_obj;
	t_image		*img_set;
	t_image		tex_set[6];
}	t_game_struct;

int		ft_error(char *str, t_game_struct *g_obj);
int		ft_strrcmp(const char *str, const char *target);

void	print_map(t_game_struct *g_obj);

#endif