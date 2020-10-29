/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_filler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 03:51:34 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 15:34:05 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int			str_char_count(char *tab)
{
	int	i;

	i = 0;
	while (*tab)
		if (*tab++ != 32)
			i++;
	return (i);
}

static void	orienter(t_info *ptr, double dir)
{
	double	olddirx;
	double	oldplanex;

	olddirx = ptr->p_look_x;
	oldplanex = ptr->w_plane_x;
	ptr->p_look_x = ptr->p_look_x * cos(dir) - ptr->p_look_y * sin(dir);
	ptr->p_look_y = olddirx * sin(dir) + ptr->p_look_y * cos(dir);
	ptr->w_plane_x = ptr->w_plane_x * cos(dir) - ptr->w_plane_y * sin(dir);
	ptr->w_plane_y = oldplanex * sin(dir) + ptr->w_plane_y * cos(dir);
}

static void	char_ori(t_info *info, char c)
{
	if (c == 'E')
	{
		orienter(info, 0 * info->p_rot_speed);
		info->p_look_x = 1.0;
		info->p_look_y = 0.0;
	}
	else if (c == 'W')
	{
		orienter(info, 18 * info->p_rot_speed);
		info->p_look_x = -1.0;
		info->p_look_y = 0.0;
	}
	else if (c == 'N')
	{
		orienter(info, -9 * info->p_rot_speed);
		info->p_look_x = 0.0;
		info->p_look_y = -1.0;
	}
	else if (c == 'S')
	{
		orienter(info, 9 * info->p_rot_speed);
		info->p_look_x = 0.0;
		info->p_look_y = 1.0;
	}
}

double		ft_abs(double nbr)
{
	return ((nbr < 0) ? -nbr : nbr);
}

int			ft_player_poser(t_info *info)
{
	int	*i;

	i = (int[2]){0, 0};
	if (!info->map_gen)
		return (-1);
	while (info->map_gen[i[0]])
	{
		i[1] = 0;
		while (info->map_gen[i[0]][i[1]])
			if (ft_strchr("NSEW", info->map_gen[i[0]][i[1]]))
			{
				if (info->p_pos_x || info->p_pos_y)
					return (-1);
				char_ori(info, info->map_gen[i[0]][i[1]]);
				info->p_sp_face = info->map_gen[i[0]][i[1]];
				info->p_pos_y = (double)i[0] + 0.5;
				info->p_pos_x = (double)i[1]++ + 0.5;
			}
			else
				i[1]++;
		i[0]++;
	}
	if (info->p_pos_x && info->p_pos_y)
		return (0);
	return (-1);
}
