/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:16:20 by doohkim           #+#    #+#             */
/*   Updated: 2023/03/30 17:48:59 by doohkim          ###   ########.fr       */
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
	g_obj->p_obj.pos_y = 12;
	g_obj->p_obj.dir_x = -1;
	g_obj->p_obj.dir_y = 0;
	g_obj->p_obj.plane_x = 0;
	g_obj->p_obj.plane_y = 0.66;
	g_obj->f_obj.old_time = 0;
	g_obj->f_obj.time = 0;
	g_obj->f_obj.move_speed = 5.0 / 30.0;
	g_obj->f_obj.rot_speed = 3.0 / 30.0;
}

t_image	*new_scene(void *mlx_ptr)
{
	t_image	*new_img;

	new_img = (t_image *)ft_calloc(1, sizeof(t_image));
	if (!new_img)
		return (NULL);
	new_img->img_ptr = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
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

void	put_pixel(t_game_struct *g_obj, int idx, char *color)
{
	g_obj->img_set->img_data[idx] = color[0];
	g_obj->img_set->img_data[idx + 1] = color[1];
	g_obj->img_set->img_data[idx + 2] = color[2];
	g_obj->img_set->img_data[idx + 3] = color[3];
}

void	draw_line(t_game_struct *g_obj, int x, int draw_start, int draw_end, char *color)
{
	int	idx;

	while (draw_start < draw_end)
	{
		idx = x * 4 + g_obj->img_set->size_line * draw_start;
		put_pixel(g_obj, idx, color);
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
		cam_x = 2 * x / (double) WIN_WIDTH - 1;
		ray_dir_x = g_obj->p_obj.dir_x + g_obj->p_obj.plane_x * cam_x;
		ray_dir_y = g_obj->p_obj.dir_y + g_obj->p_obj.plane_y * cam_x;
		map_x = (int) g_obj->p_obj.pos_x;
		map_y = (int) g_obj->p_obj.pos_y;
		delta_dist_x = fabs(1.0 / ray_dir_x);
		delta_dist_y = fabs(1.0 / ray_dir_y);
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
			if (g_obj->map_arr[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - g_obj->p_obj.pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - g_obj->p_obj.pos_y + (1 - step_y) / 2) / ray_dir_y;

		line_height = (int)(WIN_HEIGHT / perp_wall_dist);

		// 윗 지점
		draw_start = WIN_HEIGHT / 2 - line_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		// 아랫 지점
		draw_end = WIN_HEIGHT / 2 + line_height / 2 ;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		
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
		tex_pos = (double)(draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
		
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
			if (side == 1)
			{
				color[0] = (char)((unsigned char)color[0] / 2);
				color[1] = (char)((unsigned char)color[1] / 2);
				color[2] = (char)((unsigned char)color[2] / 2);
			}
			idx = x * 4 +g_obj->img_set->size_line * y;
			put_pixel(g_obj, idx, color);
			y++;
		}
		//draw_line(g_obj, x, draw_start, draw_end, color);
		draw_line(g_obj, x, draw_end, WIN_HEIGHT, (char []){127, 127, 0, 0});
		x++;
	}
}

int	ft_destroy(t_game_struct *g_obj)
{
	mlx_destroy_image(g_obj->mlx_ptr, g_obj->img_set->img_ptr);
	free(g_obj->img_set);
	mlx_destroy_window(g_obj->mlx_ptr, g_obj->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

void	clear_screen(t_game_struct *g_obj)
{
	ft_memset(g_obj->img_set->img_data, 0, g_obj->img_set->size_line * WIN_HEIGHT);
	mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_set->img_ptr, 0, 0);
}

int	ft_key_hook(int keycode, t_game_struct *g_obj)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == ESC_KEY)
		ft_destroy(g_obj);
	else if (keycode == LEFT_KEY)
	{
		old_dir_x = g_obj->p_obj.dir_x;
		g_obj->p_obj.dir_x = g_obj->p_obj.dir_x * cos(g_obj->f_obj.rot_speed) - g_obj->p_obj.dir_y * sin(g_obj->f_obj.rot_speed);
		g_obj->p_obj.dir_y = old_dir_x * sin(g_obj->f_obj.rot_speed) + g_obj->p_obj.dir_y * cos(g_obj->f_obj.rot_speed);
		old_plane_x = g_obj->p_obj.plane_x;
		g_obj->p_obj.plane_x = g_obj->p_obj.plane_x * cos(g_obj->f_obj.rot_speed) - g_obj->p_obj.plane_y * sin(g_obj->f_obj.rot_speed);
		g_obj->p_obj.plane_y = old_plane_x * sin(g_obj->f_obj.rot_speed) + g_obj->p_obj.plane_y * cos(g_obj->f_obj.rot_speed);
		clear_screen(g_obj);
		draw_scene(g_obj);
		mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_set->img_ptr, 0, 0);
	}
	else if (keycode == RIGHT_KEY)
	{
		old_dir_x = g_obj->p_obj.dir_x;
		g_obj->p_obj.dir_x = g_obj->p_obj.dir_x * cos(-g_obj->f_obj.rot_speed) - g_obj->p_obj.dir_y * sin(-g_obj->f_obj.rot_speed);
		g_obj->p_obj.dir_y = old_dir_x * sin(-g_obj->f_obj.rot_speed) + g_obj->p_obj.dir_y * cos(-g_obj->f_obj.rot_speed);
		old_plane_x = g_obj->p_obj.plane_x;
		g_obj->p_obj.plane_x = g_obj->p_obj.plane_x * cos(-g_obj->f_obj.rot_speed) - g_obj->p_obj.plane_y * sin(-g_obj->f_obj.rot_speed);
		g_obj->p_obj.plane_y = old_plane_x * sin(-g_obj->f_obj.rot_speed) + g_obj->p_obj.plane_y * cos(-g_obj->f_obj.rot_speed);
		clear_screen(g_obj);
		draw_scene(g_obj);
		mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_set->img_ptr, 0, 0);
	}
	else if (keycode == W_KEY)
	{
		if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x + 2.0 * g_obj->p_obj.dir_x * g_obj->f_obj.move_speed)][(int)g_obj->p_obj.pos_y] == 0)
			g_obj->p_obj.pos_x += g_obj->p_obj.dir_x * g_obj->f_obj.move_speed;
		if (g_obj->map_arr[(int)g_obj->p_obj.pos_x][(int)(g_obj->p_obj.pos_y + 2.0 * g_obj->p_obj.dir_y * g_obj->f_obj.move_speed)] == 0)
			g_obj->p_obj.pos_y += g_obj->p_obj.dir_y * g_obj->f_obj.move_speed;
		clear_screen(g_obj);
		draw_scene(g_obj);
		mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_set->img_ptr, 0, 0);
	}
	else if (keycode == S_KEY)
	{
		if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x - 2.0 * g_obj->p_obj.dir_x * g_obj->f_obj.move_speed)][(int)g_obj->p_obj.pos_y] == 0)
			g_obj->p_obj.pos_x -= g_obj->p_obj.dir_x * g_obj->f_obj.move_speed;
		if (g_obj->map_arr[(int)g_obj->p_obj.pos_x][(int)(g_obj->p_obj.pos_y - 2.0 * g_obj->p_obj.dir_y * g_obj->f_obj.move_speed)] == 0)
			g_obj->p_obj.pos_y -= g_obj->p_obj.dir_y * g_obj->f_obj.move_speed;
		clear_screen(g_obj);
		draw_scene(g_obj);
		mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_set->img_ptr, 0, 0);
	}
	// 좌우 벽에 붙으면 bux error가 일어나는 이슈
	// 레이 캐스팅 계산시 start,end 지점이 터무니 없이 계산되는 문제로 추정
	// 임시로 검사할 때 두 배씩 하는 방법을 했지만, 모서리 접근시? 벽이 절반을 뒤덮을시? bus error
	else if (keycode == A_KEY)
	{
		if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x - 2.0 * g_obj->p_obj.dir_y * g_obj->f_obj.move_speed)][(int)g_obj->p_obj.pos_y] == 0)
			g_obj->p_obj.pos_x -= g_obj->p_obj.dir_y * g_obj->f_obj.move_speed;
		if (g_obj->map_arr[(int)g_obj->p_obj.pos_x][(int)(g_obj->p_obj.pos_y + 2.0 * g_obj->p_obj.dir_x * g_obj->f_obj.move_speed)] == 0)
			g_obj->p_obj.pos_y += g_obj->p_obj.dir_x * g_obj->f_obj.move_speed;
		clear_screen(g_obj);
		draw_scene(g_obj);
		mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_set->img_ptr, 0, 0);
	}
	else if (keycode == D_KEY)
	{
		if (g_obj->map_arr[(int)(g_obj->p_obj.pos_x + 2.0 * g_obj->p_obj.dir_y * g_obj->f_obj.move_speed)][(int)g_obj->p_obj.pos_y] == 0)
			g_obj->p_obj.pos_x += g_obj->p_obj.dir_y * g_obj->f_obj.move_speed;
		if (g_obj->map_arr[(int)g_obj->p_obj.pos_x][(int)(g_obj->p_obj.pos_y - 2.0 * g_obj->p_obj.dir_x * g_obj->f_obj.move_speed)] == 0)
			g_obj->p_obj.pos_y -= g_obj->p_obj.dir_x * g_obj->f_obj.move_speed;
		clear_screen(g_obj);
		draw_scene(g_obj);
		mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_set->img_ptr, 0, 0);
	}
	else if (keycode == SPACE_KEY)
		g_obj->f_obj.move_speed = 10.0 / 30.0;
	return (0);
}

int	ft_keyup_hook(int keycode, t_game_struct *g_obj)
{
	if (keycode == SPACE_KEY)
		g_obj->f_obj.move_speed = 5.0 / 30.0;
	return (0);
}

void	start_game(t_game_struct *g_obj)
{
	g_obj->img_set = new_scene(g_obj->mlx_ptr);
	if (!g_obj->img_set)
		return ;
	draw_scene(g_obj);
	g_obj->win_ptr = mlx_new_window(g_obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!g_obj->win_ptr)
		return ;
	mlx_put_image_to_window(g_obj->mlx_ptr, g_obj->win_ptr, g_obj->img_set->img_ptr, 0, 0);
	mlx_hook(g_obj->win_ptr, ON_KEYDOWN, 0, ft_key_hook, g_obj);
	mlx_hook(g_obj->win_ptr, ON_KEYUP, 0, ft_keyup_hook, g_obj);
	mlx_hook(g_obj->win_ptr, ON_DESTROY, 0, ft_destroy, g_obj);
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
		g_obj->tex_set[idx].img_ptr = mlx_xpm_file_to_image(g_obj->mlx_ptr, r_line, &g_obj->tex_set[idx].pixel_x, &g_obj->tex_set[idx].pixel_y);
		g_obj->tex_set[idx].img_data = mlx_get_data_addr(g_obj->tex_set[idx].img_ptr, &g_obj->tex_set[idx].bits_per_pixel, &g_obj->tex_set[idx].size_line, &g_obj->tex_set[idx].endian);
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
