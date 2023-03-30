/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:24:27 by doohkim           #+#    #+#             */
/*   Updated: 2023/03/21 15:28:01 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gnl_save_str(t_fd **save_fd, char *str)
{
	ssize_t	idx;

	idx = gnl_strichr(str, '\n') + 1;
	if (!idx)
		idx = gnl_strlen(str);
	(*save_fd)->len = 0;
	while (str[idx])
		(*save_fd)->buf[(*save_fd)->len++] = str[idx++];
	(*save_fd)->buf[(*save_fd)->len] = 0;
	return ;
}

static char	*gnl_print_save(t_fd **save_fd, int *is_save_fd)
{
	char	*print_str;
	ssize_t	idx;
	ssize_t	end;

	end = gnl_strichr((*save_fd)->buf, '\n') + 1;
	print_str = (char *)gnl_calloc(end + 1, sizeof(char));
	if (!print_str)
	{
		*is_save_fd = 0;
		return ((void *)0);
	}
	idx = 0;
	while (++idx <= end)
		print_str[idx - 1] = (*save_fd)->buf[idx - 1];
	idx--;
	while ((*save_fd)->buf[idx])
	{
		(*save_fd)->buf[idx - end] = (*save_fd)->buf[idx];
		idx++;
	}
	(*save_fd)->buf[idx - end] = 0;
	(*save_fd)->len = idx - end;
	*is_save_fd = 1;
	return (print_str);
}

static char	*gnl_read_str(int fd, int s_len, int *is_save_fd)
{
	char	inner_buf[BUFFER_SIZE + 1];
	char	*read_str;
	int		read_size;

	read_size = read(fd, inner_buf, BUFFER_SIZE);
	*is_save_fd = read_size;
	if (read_size < 0)
		return (0);
	inner_buf[BUFFER_SIZE] = 0;
	if (gnl_strichr(inner_buf, '\n') == -1 && read_size > 0)
		read_str = gnl_read_str(fd, read_size + s_len, is_save_fd);
	else
		read_str = (char *)gnl_calloc(read_size + s_len + 1, sizeof(char));
	if (!read_str)
	{
		*is_save_fd = 0;
		return ((void *)0);
	}
	while (--read_size >= 0)
			read_str[read_size + s_len] = inner_buf[read_size];
	return (read_str);
}

static char	*ft_get_next_line(t_fd *save_fd, int *is_save_fd)
{
	char		*read_str;
	char		*result_str;

	result_str = 0;
	if (gnl_strichr(save_fd->buf, '\n') != -1)
		return (gnl_print_save(&save_fd, is_save_fd));
	read_str = gnl_read_str(save_fd->fd, 0, is_save_fd);
	if (read_str && (save_fd->buf[0] || read_str[0]))
	{
		result_str = gnl_strjoin(save_fd, read_str, is_save_fd);
		gnl_save_str(&save_fd, read_str);
	}
	if (read_str)
		free(read_str);
	return (result_str);
}

char	*get_next_line(int fd)
{
	static t_fd	*save_fd = (void *)0;
	char		*result_str;
	int			is_save_fd;

	if (fd == -1)
	{
		ft_clear_fd(&save_fd);
		return ((void *)0);
	}
	if (!save_fd)
	{
		save_fd = gnl_create_fd(fd);
		if (!save_fd)
			return ((void *)0);
	}
	result_str = ft_get_next_line(save_fd, &is_save_fd);
	if (is_save_fd < 1)
		ft_clear_fd(&save_fd);
	return (result_str);
}
