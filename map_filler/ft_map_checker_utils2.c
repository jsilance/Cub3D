/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_checker_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:47:03 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 19:56:52 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	is_file_exist(t_info *info)
{
	int	*i;

	i = (int[7]){open(info->texture_north, O_RDONLY), open(info->texture_south,
	O_RDONLY), open(info->texture_east, O_RDONLY), open(info->texture_west,
	O_RDONLY), open(info->texture_sprite, O_RDONLY), 0, 0};
	while (i[5] < 5)
	{
		if (i[i[5]] < 0)
			i[6]++;
		close(i[i[5]++]);
	}
	if (i[6])
		ft_error(8, -1, info, 1);
}

int		ft_parsing(t_info *t, char *line, int fd, int i)
{
	while (get_next_line(fd, &line) == 1)
	{
		if (!t->pa_ismap && line && ft_strchr("RSNEWFC", line[0]) &&
			++t->map_total_flags)
			info_part_one(t, line);
		else if (t->pa_ismap && !line[0])
			ft_error(6, -1, t, 0);
		else
		{
			while (line[i] && line[i] == 32)
				i++;
			if (ft_isdigit(line[i]))
			{
				if (!(t->map_gen = ft_realloc_d_malloc(t->map_gen, line, t)) ||
					t->map_total_flags < 8 || !(++t->pa_ismap))
					return (-1);
			}
			else
				ft_error(6, -1, t, 0);
		}
		free(line);
	}
	return (0);
}
