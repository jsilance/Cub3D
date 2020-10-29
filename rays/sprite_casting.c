/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:20:13 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 20:20:30 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	sprite_cast_init(t_info *t)
{
	t->s.s_sptdist = ((t->p_pos_x - t->s_pos_x) * (t->p_pos_x - t->s_pos_x) +
		(t->p_pos_y - t->s_pos_y) * (t->p_pos_y - t->s_pos_y));
	t->s.sprite_x = t->s_pos_x - t->p_pos_x;
	t->s.sprite_y = t->s_pos_y - t->p_pos_y;
	t->s.invdet = 1.0 / (t->w_plane_x * t->p_look_y - t->p_look_x *
		t->w_plane_y);
	t->s.trans_x = t->s.invdet * (t->p_look_y * t->s.sprite_x - t->p_look_x *
		t->s.sprite_y);
	t->s.trans_y = t->s.invdet * (-t->w_plane_y * t->s.sprite_x + t->w_plane_x
		* t->s.sprite_y);
	t->s.s_screen_x = (t->reso_x / 2) * (1 + t->s.trans_x / t->s.trans_y);
	t->s.s_height = ft_abs(t->reso_y / (t->s.trans_y));
	t->s.i_drawstart_y = -t->s.s_height / 2 + t->reso_y / 2;
	if (t->s.i_drawstart_y < 0)
		t->s.i_drawstart_y = 0;
	t->s.i_drawend_y = t->s.s_height / 2 + t->reso_y / 2;
	if (t->s.i_drawend_y >= t->reso_y)
		t->s.i_drawend_y = t->reso_y - 1;
	t->s.s_width = ft_abs(t->reso_y / (t->s.trans_y));
	t->s.i_drawstart_x = -t->s.s_width / 2 + t->s.s_screen_x;
	if (t->s.i_drawstart_x < 0)
		t->s.i_drawstart_x = 0;
	t->s.i_drawend_x = t->s.s_width / 2 + t->s.s_screen_x;
}

int			sprite_casting(t_info *t, double *zbuf, int y)
{
	sprite_cast_init(t);
	if (t->s.i_drawend_x >= t->reso_x)
		t->s.i_drawend_x = t->reso_x - 1;
	t->s.stripe = t->s.i_drawstart_x;
	while (t->s.stripe < t->s.i_drawend_x)
	{
		t->t_texx = (256 * (t->s.stripe - (-t->s.s_width / 2 +
			t->s.s_screen_x)) * t->texture_size_x / t->s.s_width) / 256;
		if (t->s.trans_y > 0 && t->s.stripe > 0 && t->s.stripe < t->reso_x &&
			t->s.trans_y < zbuf[t->s.stripe])
		{
			y = t->s.i_drawstart_y - 1;
			while (++y < t->s.i_drawend_y)
			{
				t->t_texy = ((((y) * 256 - t->reso_y * 128 + t->s.s_height *
					128) * t->texture_size_y) / t->s.s_height) / 256;
				t->s.color = get_pixel_color(&t->tex_f[4], t->t_texx,
					t->t_texy);
				if ((t->s.color & 0x00FFFFFF) != 0)
					t->i_addr[y * t->reso_x + t->s.stripe] = t->s.color;
			}
		}
		t->s.stripe++;
	}
}
