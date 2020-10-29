/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 04:06:05 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 19:15:04 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	ft_map_init(t_info *info)
{
	info->map_total_flags = 0;
	info->map_file = NULL;
	info->map_gen = NULL;
	info->color_roof = 0;
	info->color_ground = 0;
	info->texture_north = NULL;
	info->texture_south = NULL;
	info->texture_east = NULL;
	info->texture_west = NULL;
	info->texture_sprite = NULL;
	info->texture_size_x = 64;
	info->texture_size_y = 64;
	info->map_len_x = 0;
	info->map_len_y = 0;
	info->t_height = 64;
	info->t_width = 64;
	info->pa_ismap = 0;
}

static void	ft_window_init(t_info *info)
{
	info->mlx_ptr = NULL;
	info->window_ptr = NULL;
	info->reso_x = 0;
	info->reso_y = 0;
	info->i_screenshot = 0;
}

static void	ft_raycast_pre_init(t_info *info)
{
	info->w_cam_x = 0;
	info->w_cam_y = 0;
	info->r_ray_pos_x = 0;
	info->r_ray_pos_y = 0;
	info->r_map_x = 0;
	info->r_map_y = 0;
	info->r_ray_dir_x = 0;
	info->r_ray_dir_y = 0;
	info->w_plane_x = 0;
	info->w_plane_y = 0.66;
	info->r_side_dist_x = 0;
	info->r_side_dist_y = 0;
	info->r_delta_dist_x = 0;
	info->r_delta_dist_y = 0;
	info->r_perp_wall_dist = 0;
	info->r_step_x = 0;
	info->r_step_y = 0;
	info->r_hit = 0;
	info->r_side = 0;
	info->time = 0;
	info->old_time = 0;
}

static void	ft_p_init(t_info *info)
{
	info->p_pos_x = 0;
	info->p_pos_y = 0;
	info->p_look_x = 1;
	info->p_look_y = 1;
	info->p_sp_face = '0';
	info->p_move_speed = 1.0;
	info->p_rot_speed = 0.0174533 * 10;
}

void		struct_init(t_info *info)
{
	ft_map_init(info);
	ft_window_init(info);
	ft_p_init(info);
	ft_raycast_pre_init(info);
}
