/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:16:20 by doohkim           #+#    #+#             */
/*   Updated: 2023/04/05 17:12:36 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray_casting.h"

int	ft_check_name(char *file_str)
{
	char	**dir_splits;
	char	*file_name;
	int		split_idx;
	int		valid_check;

	dir_splits = ft_split(file_str, '/');
	split_idx = 0;
	while (dir_splits[split_idx])
		file_name = dir_splits[split_idx++];
	valid_check = ft_strrcmp(file_name, ".cub");
	ft_splits_clear(dir_splits);
	return (valid_check);
}

void	ft_create_map(int fd, t_game_struct *g_obj)
{
	char	*r_line;
	int		h_idx;
	int		w_idx;

	h_idx = 0;
	while (h_idx < MAP_HEIGHT)
	{
		r_line = get_next_line(fd);
		if (!r_line)
			break ;
		w_idx = 0;
		while (w_idx < MAP_WIDTH)
		{
			g_obj->map_arr[h_idx][w_idx] = r_line[w_idx] - '0';
			w_idx++;
		}
		free(r_line);
		h_idx++;
	}
}

void	init_obj(t_game_struct *g_obj)
{
	g_obj->p_obj.pos_x = 22;
	g_obj->p_obj.pos_y = 13;
	g_obj->p_obj.dir_x = -1;
	g_obj->p_obj.dir_y = 0;
	g_obj->p_obj.plane_x = 0;
	g_obj->p_obj.plane_y = 0.88;
	g_obj->f_obj.old_time = 0;
	g_obj->f_obj.time = 0;
	g_obj->f_obj.move_speed = 3.0 / 61.0;
	g_obj->f_obj.rot_speed = 0.75 / 61.0;
}

t_image	*new_scene(void *mlx_ptr, int width, int height)
{
	t_image	*new_img;

	new_img = (t_image *)ft_calloc(1, sizeof(t_image));
	if (!new_img)
		return (NULL);
	new_img->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!new_img->img_ptr)
	{
		free(new_img);
		return (NULL);
	}
	new_img->img_data = mlx_get_data_addr(new_img->img_ptr, \
			&new_img->bits_per_pixel, &new_img->size_line, &new_img->endian);
	if (!new_img->img_data)
	{
		mlx_destroy_image(mlx_ptr, new_img->img_ptr);
		free(new_img);
		return (NULL);
	}
	return (new_img);
}

void	put_pixel(t_image *img, int idx, char *color)
{
	img->img_data[idx] = color[0];
	img->img_data[idx + 1] = color[1];
	img->img_data[idx + 2] = color[2];
	img->img_data[idx + 3] = color[3];
}

void	draw_line(t_game_struct *g_obj, int x, int draw_start, int draw_end, char *color)
{
	int	idx;

	while (draw_start < draw_end)
	{
		idx = x * 4 + g_obj->img_buf[g_obj->buf_idx]->size_line * draw_start;
		put_pixel(g_obj->img_buf[g_obj->buf_idx], idx, color);
		draw_start++;
	}
}

void	draw_scene(t_game_struct *g_obj)
{
	int		x, map_x, map_y, step_x, step_y, hit, side, line_height, draw_start, draw_end;
	double	cam_x, ray_dir_x, ray_dir_y, side_dist_x, side_dist_y, delta_dist_x, delta_dist_y, perp_wall_dist;
	int		tex_num, tex_x, tex_y, y, idx;
	double	wall_x, step, tex_pos;
	char	color[4];

	ft_memset(color, 0, sizeof(color));
	x = 0;
	while (x < WIN_WIDTH)
	{
		cam_x = 2 * x / (double)WIN_WIDTH - 1;
		ray_dir_x = g_obj->p_obj.dir_x + g_obj->p_obj.plane_x * cam_x;
		ray_dir_y = g_obj->p_obj.dir_y + g_obj->p_obj.plane_y * cam_x;
		map_x = (int)g_obj->p_obj.pos_x;
		map_y = (int)g_obj->p_obj.pos_y;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		hit = 0;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (g_obj->p_obj.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - g_obj->p_obj.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (g_obj->p_obj.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - g_obj->p_obj.pos_y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (g_obj->map_arr[map_x][map_y] != 0)
				hit = 1;
		}
		if (side == 0)
		{
			perp_wall_dist = (map_x - g_obj->p_obj.pos_x + (1 - step_x) / 2.0) / ray_dir_x;
		}
		else
			perp_wall_dist = (map_y - g_obj->p_obj.pos_y + (1 - step_y) / 2.0) / ray_dir_y;

		// printf("x: %d %f\n", map_x, g_obj->p_obj.pos_x);
		// printf("y: %d %f\n", map_y, g_obj->p_obj.pos_y);
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);

		// 윗 지점
		draw_start =  -line_height / 2 + WIN_HEIGHT / 2;
		draw_end = WIN_HEIGHT / 2 + line_height / 2 ;
		if (draw_start < 0)
			draw_start = 0;
		// 아랫 지점
		if (draw_end >= (int)WIN_HEIGHT)
			draw_end = (int)WIN_HEIGHT - 1;
		
		tex_num = g_obj->map_arr[map_x][map_y];
		
		if (side == 0)
			wall_x = g_obj->p_obj.pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = g_obj->p_obj.pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		
		tex_x = (int)(wall_x * 64.0);
		if (side == 0 && ray_dir_x > 0)
			tex_x = 64 - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = 64 - tex_x - 1;
		
		step = 64.0 / (double)line_height;
		tex_pos = (double)(draw_start - WIN_HEIGHT / 2.0 + line_height / 2.0) * step;
		
		/*
		// 텍스쳐없이 color로만 렌더링
		if (g_obj->map_arr[map_x][map_y] == 1)
			color[2] = -1;
		else if (g_obj->map_arr[map_x][map_y] == 2)
			color[1] = -1;
		else if (g_obj->map_arr[map_x][map_y] == 3)
			color[0] = -1;
		else if (g_obj->map_arr[map_x][map_y] == 4)
		{
			color[0] = -1;
			color[1] = -1;
			color[2] = -1;
		}
		else
		{
			color[1] = -1;
			color[2] = -1;
		}

		if (side == 1)
		{
			if (color[0])
				color[0] = -128;
			if (color[1])
				color[1] = -128;
			if (color[2])
				color[2] = -128;
		}
		*/
		//draw the pixels of the stripe as a vertical line
		// 해당 x좌표의 세로 라인을 전부 그린다 draw_start(시작지점), draw_end(끝지점)
		// 0 ~ start: 천장
		// end ~ height: 바닥
		draw_line(g_obj, x, 0, draw_start, (char []){64, 64, 64, 0});
		y = draw_start;
		while (y < draw_end)
		{
			tex_y = (int)tex_pos & 63;
			tex_pos += step;
			color[0] = g_obj->tex_set[tex_num].img_data[tex_x * 4 + g_obj->tex_set[tex_num].size_line * tex_y];
			color[1] = g_obj->tex_set[tex_num].img_data[tex_x * 4 + g_obj->tex_set[tex_num].size_line * tex_y + 1];
			color[2] = g_obj->tex_set[tex_num].img_data[tex_x * 4 + g_obj->tex_set[tex_num].size_line * tex_y + 2];
			color[3] = g_obj->tex_set[tex_num].img_data[tex_x * 4 + g_obj->tex_set[tex_num].size_line * tex_y + 3];
			if (side == 0 && step_x == 1)
			{
				color[0] = (char)((unsigned char)color[0] / 8);
				color[1] = (char)((unsigned char)color[1] / 8);
				color[2] = (char)((unsigned char)color[2] / 8);
			}
			if (side == 1 && step_y == -1)
			{
				color[0] = (char)((unsigned char)color[0] / 2);
				color[1] = (char)((unsigned char)color[1] / 2);
				color[2] = (char)((unsigned char)color[2] / 2);
			}
			if (side == 1 && step_y == 1)
			{
				color[0] = (char)((unsigned char)color[0] / 4);
				color[1] = (char)((unsigned char)color[1] / 4);
				color[2] = (char)((unsigned char)color[2] / 4);
			}
			idx = x * 4 + g_obj->img_buf[g_obj->buf_idx]->size_line * y;
			put_pixel(g_obj->img_buf[g_obj->buf_idx], idx, color);
			y++;
		}
		//draw_line(g_obj, x, draw_start, draw_end, color);
		draw_line(g_obj, x, draw_end, WIN_HEIGHT, (char []){127, 127, 0, 0});
		x++;
	}
}

void	minimap_player(t_image *img, char *color)
{
	int	x_idx;
	int	y_idx;
	int	idx;

	y_idx = MIN_MAP_H / 2 - 4;
	while (y_idx < MIN_MAP_H / 2 + 4)
	{
		x_idx = MIN_MAP_W / 2 - 4;
		while (x_idx < MIN_MAP_W / 2 + 4)
		{
			idx = x_idx * 4 + img->size_line * y_idx;
			put_pixel(img, idx, color);
			x_idx++;
		}
		y_idx++;
	}
}

void	minimap_wall(t_game_struct *g_obj, int p_x_idx, int p_y_idx, char *color)
{
	int	x_idx;
	int	y_idx;
	int	idx;

	y_idx = -p_y_idx;
	while (y_idx + p_y_idx < MIN_MAP_H)
	{
		if (g_obj->p_obj.pos_x + (double)y_idx * 0.05 >= (double)0 \
			&& g_obj->p_obj.pos_x + (double)y_idx * 0.05 < (double)MAP_HEIGHT)
		{
			x_idx = -p_x_idx;
			while (x_idx + p_x_idx < MIN_MAP_W)
			{
				if (g_obj->p_obj.pos_y + (double)x_idx * 0.05 >= (double)0 \
					&& g_obj->p_obj.pos_y + (double)x_idx * 0.05 < (double)MAP_WIDTH)
				{
					if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x + (double)y_idx * 0.05)][(int)(g_obj->p_obj.pos_y + (double)x_idx * 0.05)] > 0)
					{
						idx = (x_idx + p_x_idx) * 4 + g_obj->min_map[g_obj->buf_idx]->size_line * (y_idx + p_y_idx);
						put_pixel(g_obj->min_map[g_obj->buf_idx], idx, color);
					}
				}
				x_idx++;
			}
		}
		y_idx++;
	}
}

void	draw_minimap(t_game_struct *g_obj)
{
	char	w_color[4];
	char	p_color[4];

	if (!g_obj->map_view)
		return ;
	ft_memset(g_obj->min_map[g_obj->buf_idx]->img_data, -128, g_obj->min_map[g_obj->buf_idx]->size_line * MIN_MAP_H);
	ft_memset(w_color, 0, sizeof(w_color));
	w_color[0] = -128;
	ft_memset(p_color, 0, sizeof(p_color));
	p_color[2] = -128;
	mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->min_map[g_obj->buf_idx]->img_ptr, 0, 0);
	minimap_wall(g_obj, MIN_MAP_W / 2, MIN_MAP_H / 2, w_color);
	minimap_player(g_obj->min_map[g_obj->buf_idx], p_color);
	mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->min_map[g_obj->buf_idx]->img_ptr, 0, 0);
}

/*
void	draw_front(t_game_struct *g_obj)
{
	ft_memmove(g_obj->front_buf->img_data, g_obj->back_buf->img_data, g_obj->back_buf->size_line * WIN_HEIGHT);
}
*/

int	ft_destroy(t_game_struct *g_obj)
{
	mlx_destroy_image(g_obj->mlx_ptr, g_obj->img_buf[0]->img_ptr);
	mlx_destroy_image(g_obj->mlx_ptr, g_obj->img_buf[1]->img_ptr);
	mlx_destroy_image(g_obj->mlx_ptr, g_obj->min_map[0]->img_ptr);
	mlx_destroy_image(g_obj->mlx_ptr, g_obj->min_map[1]->img_ptr);
	free(g_obj->img_buf[0]);
	free(g_obj->img_buf[1]);
	free(g_obj->min_map[0]);
	free(g_obj->min_map[1]);
	mlx_destroy_window(g_obj->mlx_ptr, g_obj->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

/*
void	clear_screen(t_game_struct *g_obj)
{
	ft_memset(g_obj->back_buf->img_data, 0, g_obj->back_buf->size_line * WIN_HEIGHT);
}
*/

int	ft_key_hook(int keycode, t_game_struct *g_obj)
{
	if (keycode == ESC_KEY)
		ft_destroy(g_obj);
	else if (keycode == W_KEY)
		g_obj->key_press[UP_PRESS] = 1;
	else if (keycode == S_KEY)
		g_obj->key_press[DOWN_PRESS] = 1;
	else if (keycode == A_KEY)
		g_obj->key_press[LEFT_PRESS] = 1;
	else if (keycode == D_KEY)
		g_obj->key_press[RIGHT_PRESS] = 1;
	else if (keycode == SPACE_KEY)
		g_obj->f_obj.move_speed = 6.0 / 61.0;
	else if (keycode == P_KEY)
	{
		if (!g_obj->view_change)
			g_obj->view_change = 1;
		else
			g_obj->view_change = 0;
		g_obj->view_move = NO_MOVE;
	}
	else if (keycode == M_KEY)
	{
		if (!g_obj->map_view)
			g_obj->map_view = 1;
		else
			g_obj->map_view = 0;
	}
	else if (keycode == LEFT_KEY && !g_obj->view_change)
		g_obj->view_move = LEFT_MOVE;
	else if (keycode == RIGHT_KEY && !g_obj->view_change)
		g_obj->view_move = RIGHT_MOVE;
	return (0);
}

int	ft_keyup_hook(int keycode, t_game_struct *g_obj)
{
	if (keycode == W_KEY)
		g_obj->key_press[UP_PRESS] = 0;
	else if (keycode == S_KEY)
		g_obj->key_press[DOWN_PRESS] = 0;
	else if (keycode == A_KEY)
		g_obj->key_press[LEFT_PRESS] = 0;
	else if (keycode == D_KEY)
		g_obj->key_press[RIGHT_PRESS] = 0;
	else if (keycode == LEFT_KEY && !g_obj->view_change)
		g_obj->view_move = NO_MOVE;
	else if (keycode == RIGHT_KEY && !g_obj->view_change)
		g_obj->view_move = NO_MOVE;
	else if (keycode == SPACE_KEY)
		g_obj->f_obj.move_speed = 5.0 / 60.0;
	return (0);
}

int	ft_view_move(int x, int y, t_game_struct *g_obj)
{
	(void)y;
	if (!g_obj->view_change)
		return (0);
	if (x < WIN_WIDTH / 4)
	{
		if (x < 0)
			g_obj->f_obj.rot_speed = 1.5 / 61.0;
		else
			g_obj->f_obj.rot_speed = 0.75 / 61.0;
		g_obj->view_move = LEFT_MOVE;
	}
	else if (x > WIN_WIDTH / 4 * 3)
	{
		if (x > WIN_WIDTH)
			g_obj->f_obj.rot_speed = 1.5 / 61.0;
		else
			g_obj->f_obj.rot_speed = 0.75 / 61.0;
		g_obj->view_move = RIGHT_MOVE;
	}
	else
		g_obj->view_move = NO_MOVE;
	return (0);
}

int	ft_loop_hook(t_game_struct *g_obj)
{
	double	old_dir_x;
	double	old_plane_x;

	// 좌우 벽에 붙으면 bux error가 일어나는 이슈
	// 레이 캐스팅 계산시 start,end 지점이 터무니 없이 계산되는 문제로 추정
	// 임시로 검사할 때 두 배씩 하는 방법을 했지만, 모서리 접근시? 벽이 절반을 뒤덮을시? bus error
	if (g_obj->buf_idx)
		g_obj->buf_idx = 0;
	else
		g_obj->buf_idx = 1;
	if (g_obj->view_move == LEFT_MOVE)
	{
		old_dir_x = g_obj->p_obj.dir_x;
		g_obj->p_obj.dir_x = g_obj->p_obj.dir_x * cos(g_obj->f_obj.rot_speed) - g_obj->p_obj.dir_y * sin(g_obj->f_obj.rot_speed);
		g_obj->p_obj.dir_y = old_dir_x * sin(g_obj->f_obj.rot_speed) + g_obj->p_obj.dir_y * cos(g_obj->f_obj.rot_speed);
		old_plane_x = g_obj->p_obj.plane_x;
		g_obj->p_obj.plane_x = g_obj->p_obj.plane_x * cos(g_obj->f_obj.rot_speed) - g_obj->p_obj.plane_y * sin(g_obj->f_obj.rot_speed);
		g_obj->p_obj.plane_y = old_plane_x * sin(g_obj->f_obj.rot_speed) + g_obj->p_obj.plane_y * cos(g_obj->f_obj.rot_speed);
	}
	if (g_obj->view_move == RIGHT_MOVE)
	{
		old_dir_x = g_obj->p_obj.dir_x;
		g_obj->p_obj.dir_x = g_obj->p_obj.dir_x * cos(-g_obj->f_obj.rot_speed) - g_obj->p_obj.dir_y * sin(-g_obj->f_obj.rot_speed);
		g_obj->p_obj.dir_y = old_dir_x * sin(-g_obj->f_obj.rot_speed) + g_obj->p_obj.dir_y * cos(-g_obj->f_obj.rot_speed);
		old_plane_x = g_obj->p_obj.plane_x;
		g_obj->p_obj.plane_x = g_obj->p_obj.plane_x * cos(-g_obj->f_obj.rot_speed) - g_obj->p_obj.plane_y * sin(-g_obj->f_obj.rot_speed);
		g_obj->p_obj.plane_y = old_plane_x * sin(-g_obj->f_obj.rot_speed) + g_obj->p_obj.plane_y * cos(-g_obj->f_obj.rot_speed);
	}
	if (g_obj->key_press[UP_PRESS])
	{
		if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x + g_obj->p_obj.dir_x * g_obj->f_obj.move_speed)][(int)g_obj->p_obj.pos_y] == 0)
			g_obj->p_obj.pos_x += g_obj->p_obj.dir_x * g_obj->f_obj.move_speed;
		if (g_obj->map_arr[(int)g_obj->p_obj.pos_x][(int)(g_obj->p_obj.pos_y + g_obj->p_obj.dir_y * g_obj->f_obj.move_speed)] == 0)
			g_obj->p_obj.pos_y += g_obj->p_obj.dir_y * g_obj->f_obj.move_speed;
	}
	if (g_obj->key_press[DOWN_PRESS])
	{
		if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x - g_obj->p_obj.dir_x * g_obj->f_obj.move_speed)][(int)g_obj->p_obj.pos_y] == 0)
			g_obj->p_obj.pos_x -= g_obj->p_obj.dir_x * g_obj->f_obj.move_speed;
		if (g_obj->map_arr[(int)g_obj->p_obj.pos_x][(int)(g_obj->p_obj.pos_y - g_obj->p_obj.dir_y * g_obj->f_obj.move_speed)] == 0)
			g_obj->p_obj.pos_y -= g_obj->p_obj.dir_y * g_obj->f_obj.move_speed;
	}
	if (g_obj->key_press[LEFT_PRESS])
	{
		if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x - g_obj->p_obj.dir_y * g_obj->f_obj.move_speed)][(int)g_obj->p_obj.pos_y] == 0)
			g_obj->p_obj.pos_x -= g_obj->p_obj.dir_y * g_obj->f_obj.move_speed;
		if (g_obj->map_arr[(int)g_obj->p_obj.pos_x][(int)(g_obj->p_obj.pos_y + g_obj->p_obj.dir_x * g_obj->f_obj.move_speed)] == 0)
			g_obj->p_obj.pos_y += g_obj->p_obj.dir_x * g_obj->f_obj.move_speed;
	}
	if (g_obj->key_press[RIGHT_PRESS])
	{
		if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x + g_obj->p_obj.dir_y * g_obj->f_obj.move_speed)][(int)g_obj->p_obj.pos_y] == 0)
			g_obj->p_obj.pos_x += g_obj->p_obj.dir_y * g_obj->f_obj.move_speed;
		if (g_obj->map_arr[(int)g_obj->p_obj.pos_x][(int)(g_obj->p_obj.pos_y - g_obj->p_obj.dir_x * g_obj->f_obj.move_speed)] == 0)
			g_obj->p_obj.pos_y -= g_obj->p_obj.dir_x * g_obj->f_obj.move_speed;
	}
	draw_scene(g_obj);
	mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_buf[g_obj->buf_idx]->img_ptr, 0, 0);
	draw_minimap(g_obj);
	return (0);
}

void	start_game(t_game_struct *g_obj)
{
	g_obj->img_buf[0] = new_scene(g_obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!g_obj->img_buf[0])
		return ;
	g_obj->img_buf[1] = new_scene(g_obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!g_obj->img_buf[1])
		return ;
	g_obj->min_map[0] = new_scene(g_obj->mlx_ptr, MIN_MAP_W, MIN_MAP_H);
	if (!g_obj->min_map[0])
		return ;
	g_obj->min_map[1] = new_scene(g_obj->mlx_ptr, MIN_MAP_W, MIN_MAP_H);
	if (!g_obj->min_map[1])
		return ;
	g_obj->win_ptr = mlx_new_window(g_obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, \
									"cub3d");
	if (!g_obj->win_ptr)
		return ;
	draw_scene(g_obj);
	mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, \
							g_obj->img_buf[g_obj->buf_idx]->img_ptr, 0, 0);
	draw_minimap(g_obj);
	mlx_hook(g_obj->win_ptr, ON_KEYDOWN, 0, ft_key_hook, g_obj);
	mlx_hook(g_obj->win_ptr, ON_KEYUP, 0, ft_keyup_hook, g_obj);
	mlx_hook(g_obj->win_ptr, ON_DESTROY, 0, ft_destroy, g_obj);
	mlx_hook(g_obj->win_ptr, ON_MOUSEMOVE, 0, ft_view_move, g_obj);
	mlx_loop_hook(g_obj->mlx_ptr, ft_loop_hook, g_obj);
	mlx_loop(g_obj->mlx_ptr);
}

void	read_texture(int fd, t_game_struct *g_obj)
{
	char	*r_line;
	int		idx;

	idx = 0;
	while (1)
	{
		r_line = get_next_line(fd);
		if (!ft_strncmp(r_line, "\n", ft_strlen("\n")))
			break ;
		if (r_line[ft_strlen(r_line) - 1] == '\n')
			r_line[ft_strlen(r_line) - 1] = 0;
		g_obj->tex_set[idx].img_ptr = mlx_xpm_file_to_image(g_obj->mlx_ptr, \
									r_line, &g_obj->tex_set[idx].pixel_x, \
									&g_obj->tex_set[idx].pixel_y);
		g_obj->tex_set[idx].img_data = mlx_get_data_addr(\
			g_obj->tex_set[idx].img_ptr, &g_obj->tex_set[idx].bits_per_pixel, \
			&g_obj->tex_set[idx].size_line, &g_obj->tex_set[idx].endian);
		free(r_line);
		idx++;
	}
}

int	main(int argc, char **argv)
{
	t_game_struct	g_obj;
	int				fd;

	ft_memset(&g_obj, 0, sizeof(t_game_struct));
	if (argc == 1)
		return (EXIT_FAILURE);
	if (!ft_check_name(argv[1]))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			ft_error(strerror(errno), &g_obj);
		g_obj.mlx_ptr = mlx_init();
		if (!g_obj.mlx_ptr)
			return (EXIT_FAILURE);
		read_texture(fd, &g_obj);
		ft_create_map(fd, &g_obj);
		close(fd);
		//print_map(&g_obj);
		init_obj(&g_obj);
		start_game(&g_obj);
	}
	return (EXIT_SUCCESS);
}
