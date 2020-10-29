/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 21:30:19 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 18:52:19 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static unsigned char	*altox_fd(int nbyte, unsigned int val, int fd)
{
	int				i;
	unsigned char	bytes[nbyte];

	i = 0;
	while (val)
	{
		bytes[i] = val & 255;
		val = val >> 8;
		i++;
	}
	while (i < nbyte)
		bytes[i++] = 0;
	return (bytes);
}

static int				bmp_init_header(int fd, t_info *t)
{
	unsigned char	ch[54];
	char			*filetype;

	ft_memcpy(&ch[0], "B", 1);
	ft_memcpy(&ch[1], "M", 1);
	ft_memcpy(&ch[2], altox_fd(4, t->reso_y * ((t->reso_x * t->i_bpp + 31) /
		32) * 4 + 54, fd), 4);
	ft_memcpy(&ch[6], altox_fd(4, 0, fd), 4);
	ft_memcpy(&ch[10], altox_fd(4, 54, fd), 4);
	ft_memcpy(&ch[14], altox_fd(4, 40, fd), 4);
	ft_memcpy(&ch[18], altox_fd(4, t->reso_x, fd), 4);
	ft_memcpy(&ch[22], altox_fd(4, t->reso_y, fd), 4);
	ft_memcpy(&ch[26], altox_fd(2, 1, fd), 2);
	ft_memcpy(&ch[28], altox_fd(2, 32, fd), 2);
	ft_memcpy(&ch[30], altox_fd(24, 0, fd), 24);
	write(fd, ch, 54);
	return (0);
}

static void				bmp_head(int fd, t_info *t)
{
	unsigned long	i;
	int				j;
	int				k;
	unsigned char	c[4];

	j = t->reso_x * t->reso_y;
	c[3] = 0;
	k = bmp_init_header(fd, t);
	while (k++ < t->reso_y && (i = j - k * t->reso_x))
		while (i < j - (k - 1) * t->reso_x)
		{
			c[0] = t->i_addr[i] & 255;
			c[1] = t->i_addr[i] >> 8 & 255;
			c[2] = t->i_addr[i++] >> 16 & 255;
			write(fd, &c[0], 4);
		}
}

void					bmp_maker(t_info *t)
{
	int		fd;

	fd = open("Cub3D.bmp", O_WRONLY | O_CREAT, S_IRWXU);
	bmp_head(fd, t);
	if (fd >= 0)
	{
		close(fd);
		ft_duty_free(t->map_gen, t->map_len_y);
		exit(0);
	}
	else
		ft_error(5, -1, t, 1);
}
