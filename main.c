/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 02:56:04 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 20:36:18 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	ft_launch(t_info *t)
{
	if (!(t->mlx_ptr = mlx_init()) ||
		!(t->i_img = mlx_new_image(t->mlx_ptr, t->reso_x, t->reso_y)) ||
		!(t->i_addr = mlx_get_data_addr(t->i_img, &t->i_bpp, &t->i_sl,
		&t->i_endian)))
		ft_error(4, -1, t, 1);
	if (!t->i_screenshot)
	{
		if (!(t->window_ptr = mlx_new_window(t->mlx_ptr, t->reso_x,
			t->reso_y, "Cub3D")))
			ft_error(4, -1, t, 1);
		mlx_key_hook(t->window_ptr, key_pressed, t);
		mlx_hook(t->window_ptr, 17, 0, exit_hook, t);
	}
	mlx_loop_hook(t->mlx_ptr, ft_rays, t);
	mlx_loop(t->mlx_ptr);
	ft_duty_free(t->map_verif, t->map_len_y);
	ft_duty_free(t->map_gen, t->map_len_y);
}

int			main(int argc, char *argv[])
{
	t_info	info;

	struct_init(&info);
	if (argc == 1 || argc > 3)
		ft_error(0, -1, &info, 0);
	info.map_file = argv[1];
	if (ft_map_read(&info))
		ft_error(6, -1, &info, 1);
	if (argc == 3)
		if (!ft_strncmp(argv[2], "--save", 6))
			info.i_screenshot = 1;
		else
			ft_error(0, -1, &info, 1);
	ft_launch(&info);
	return (0);
}
