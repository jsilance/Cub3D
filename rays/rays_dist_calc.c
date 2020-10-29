/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_dist_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:32:50 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/21 20:57:13 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	side_dist_calc_init(t_info *t)
{
	if (t->r_ray_dir_x < 0 && (t->r_step_x = -1))
		t->r_side_dist_x = (t->p_pos_x - t->r_map_x) *
			t->r_delta_dist_x;
	else if ((t->r_step_x = 1))
		t->r_side_dist_x = (t->r_map_x + 1.0 - t->p_pos_x) * t->r_delta_dist_x;
	if (t->r_ray_dir_y < 0 && (t->r_step_y = -1))
		t->r_side_dist_y = (t->p_pos_y - t->r_map_y) *
			t->r_delta_dist_y;
	else if ((t->r_step_y = 1))
		t->r_side_dist_y = (t->r_map_y + 1.0 - t->p_pos_y) *
			t->r_delta_dist_y;
}

void		side_dist_calc(t_info *t)
{
	side_dist_calc_init(t);
	while (t->r_hit == 0)
	{
		if (t->r_side_dist_x < t->r_side_dist_y && !(t->r_side = 0))
		{
			t->r_side_dist_x += t->r_delta_dist_x;
			t->r_map_x += t->r_step_x;
			t->t_texnum = (t->r_ray_dir_x < 0) ? 1 : 3;
		}
		else if ((t->r_side = 1))
		{
			t->r_side_dist_y += t->r_delta_dist_y;
			t->r_map_y += t->r_step_y;
			t->t_texnum = (t->r_ray_dir_y < 0) ? 0 : 2;
		}
		if (t->map_gen[t->r_map_y][t->r_map_x] > '0')
		{
			if (t->map_gen[t->r_map_y][t->r_map_x] == '2' && (t->s_pos_x =
				t->r_map_x + 0.5))
				t->s_pos_y = t->r_map_y + 0.5;
			else if (!ft_strchr("NSEW", t->map_gen[t->r_map_y][t->r_map_x]))
				t->r_hit = 1;
		}
	}
}
