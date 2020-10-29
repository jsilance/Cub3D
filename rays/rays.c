/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:02:36 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 20:22:40 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	rays_cast_init(t_info *t, int x)
{
	t->w_cam_x = 2 * x / (double)t->reso_x - 1.0;
	t->r_ray_dir_x = t->p_look_x + t->w_plane_x * t->w_cam_x;
	t->r_ray_dir_y = t->p_look_y + t->w_plane_y * t->w_cam_x;
	t->r_map_x = (int)t->p_pos_x;
	t->r_map_y = (int)t->p_pos_y;
	t->r_delta_dist_x = ft_abs(1 / t->r_ray_dir_x);
	t->r_delta_dist_y = ft_abs(1 / t->r_ray_dir_y);
	t->r_hit = 0;
}

static void	wall_dist_calc(t_info *t)
{
	if (t->r_side == 0)
		t->r_perp_wall_dist = ((double)t->r_map_x - t->p_pos_x +
			(1 - t->r_step_x) / 2) / (double)t->r_ray_dir_x;
	else
		t->r_perp_wall_dist = ((double)t->r_map_y - t->p_pos_y +
			(1 - t->r_step_y) / 2) / (double)t->r_ray_dir_y;
	t->i_line_height = (int)(t->reso_y / (double)t->r_perp_wall_dist);
	t->i_draw_start = -t->i_line_height / 2 + t->reso_y / 2;
	if (t->i_draw_start < 0)
		t->i_draw_start = 0;
	t->i_draw_end = t->i_line_height / 2 + t->reso_y / 2;
	if (t->i_draw_end >= t->reso_y)
		t->i_draw_end = t->reso_y - 1;
}

static void	tex_calcul(t_info *t, int x)
{
	int		i;
	int		j;
	double	wallx;

	i = t->i_draw_start;
	wallx = (!t->r_side) ? t->p_pos_y + t->r_perp_wall_dist * t->r_ray_dir_y :
		t->p_pos_x + t->r_perp_wall_dist * t->r_ray_dir_x;
	wallx -= floor((wallx));
	t->t_texx = (int)(wallx * (double)t->t_width);
	((!t->r_side && t->r_ray_dir_x > 0) || (t->r_side && t->r_ray_dir_y < 0)) ?
		(t->t_texx = t->t_width - t->t_texx - 1) : 0;
	t->t_step = 1.0 * t->t_height / t->i_line_height;
	t->t_texpos = (t->i_draw_start - t->reso_y / 2 + t->i_line_height / 2) *
		t->t_step;
}

int			ft_rays(t_info *t)
{
	int				i;
	unsigned int	cwall;
	double			zbuf[t->reso_x];

	i = 0;
	texture_init(t);
	while (i < t->reso_x * t->reso_y)
		t->i_addr[i++] = 0;
	i = -1;
	while (++i < t->reso_x)
	{
		rays_cast_init(t, i);
		side_dist_calc(t);
		wall_dist_calc(t);
		tex_calcul(t, i);
		ver_line_color(i, t, cwall, t->r_perp_wall_dist * 8);
		zbuf[i] = t->r_perp_wall_dist;
	}
	i = -1;
	sprite_casting(t, &zbuf[0], 0);
	if (t->i_screenshot)
		bmp_maker(t);
	mlx_put_image_to_window(t->mlx_ptr, t->window_ptr, t->i_img, 0, 0);
	return (1);
}
