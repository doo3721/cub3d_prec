/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:24:42 by doohkim           #+#    #+#             */
/*   Updated: 2023/03/21 15:28:01 by doohkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	gnl_strlen(const char *s)
{
	ssize_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*gnl_calloc(ssize_t count, ssize_t size)
{
	void			*return_mem;
	unsigned char	*bzero_mem;
	ssize_t			total;
	ssize_t			idx;

	if (size && count * size / size != count)
		return ((void *)0);
	total = size * count;
	return_mem = malloc(total);
	if (!return_mem)
		return ((void *)0);
	bzero_mem = return_mem;
	idx = 0;
	while (idx < total)
		bzero_mem[idx++] = 0;
	return (return_mem);
}

ssize_t	gnl_strichr(char *str, char find_c)
{
	ssize_t	idx;

	if (!str)
		return (0);
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == find_c)
			return (idx);
		idx++;
	}
	return (-1);
}

t_fd	*gnl_create_fd(int fd)
{
	t_fd	*new_fd;

	new_fd = (t_fd *)gnl_calloc(1, sizeof(t_fd));
	if (!new_fd)
		return ((void *)0);
	new_fd->fd = fd;
	new_fd->len = 0;
	new_fd->buf[0] = 0;
	return (new_fd);
}

char	*gnl_strjoin(t_fd *save_fd, char *str, int *is_save_fd)
{
	char	*join_str;
	ssize_t	str_len;
	ssize_t	idx;

	str_len = gnl_strichr(str, '\n') + 1;
	if (!str_len)
		str_len = gnl_strlen(str);
	join_str = (char *)gnl_calloc(save_fd->len + str_len + 1, sizeof(char));
	if (!join_str)
	{
		*is_save_fd = 0;
		return ((void *)0);
	}
	idx = -1;
	while (++idx <= save_fd->len)
		join_str[idx] = save_fd->buf[idx];
	idx -= 2;
	while (++idx < save_fd->len + str_len)
		join_str[idx] = str[idx - save_fd->len];
	join_str[idx] = 0;
	return (join_str);
}
