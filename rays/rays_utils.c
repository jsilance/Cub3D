/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:40:56 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 18:22:38 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int			*get_pixel_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel /
		8));
	return (*(unsigned int *)dst);
}

static void	texture_init_bis(t_info *t)
{
	int *w;
	int *h;

	w = &t->texture_size_x;
	h = &t->texture_size_y;
	if (!(t->tex_f[0].img = mlx_xpm_file_to_image(t->mlx_ptr,
		t->texture_north, w, h)))
		ft_error(7, -1, t, 1);
	if (!(t->tex_f[1].img = mlx_xpm_file_to_image(t->mlx_ptr,
		t->texture_west, w, h)))
		ft_error(7, -1, t, 1);
	if (!(t->tex_f[2].img = mlx_xpm_file_to_image(t->mlx_ptr,
		t->texture_south, w, h)))
		ft_error(7, -1, t, 1);
	if (!(t->tex_f[3].img = mlx_xpm_file_to_image(t->mlx_ptr,
		t->texture_east, w, h)))
		ft_error(7, -1, t, 1);
	if (!(t->tex_f[4].img = mlx_xpm_file_to_image(t->mlx_ptr,
		t->texture_sprite, w, h)))
		ft_error(7, -1, t, 1);
}

void		texture_init(t_info *t)
{
	texture_init_bis(t);
	t->tex_f[0].addr = mlx_get_data_addr(t->tex_f[0].img,
		&t->tex_f[0].bits_per_pixel, &t->tex_f[0].line_length,
		&t->tex_f[0].endian);
	t->tex_f[1].addr = mlx_get_data_addr(t->tex_f[1].img,
		&t->tex_f[1].bits_per_pixel, &t->tex_f[1].line_length,
		&t->tex_f[1].endian);
	t->tex_f[2].addr = mlx_get_data_addr(t->tex_f[2].img,
		&t->tex_f[2].bits_per_pixel, &t->tex_f[2].line_length,
		&t->tex_f[2].endian);
	t->tex_f[3].addr = mlx_get_data_addr(t->tex_f[3].img,
		&t->tex_f[3].bits_per_pixel, &t->tex_f[3].line_length,
		&t->tex_f[3].endian);
	t->tex_f[4].addr = mlx_get_data_addr(t->tex_f[4].img,
		&t->tex_f[4].bits_per_pixel, &t->tex_f[4].line_length,
		&t->tex_f[4].endian);
}
