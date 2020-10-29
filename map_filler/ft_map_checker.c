/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:33:29 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 16:48:56 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	ft_closer(t_info *info, int fd, int ret)
{
	close(fd);
	return (ret);
}

static int	max_line_counter(t_info *t)
{
	int	i;
	int	j;
	int	r;

	i = 0;
	j = 0;
	r = 0;
	while (t->map_gen[i])
	{
		while (t->map_gen[i][j])
			j++;
		(r < j) ? r = j : 0;
		j = 0;
		i++;
	}
	return (r);
}

static int	map_resizer(t_info *t)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (!(t->map_verif = ft_calloc(sizeof(char), t->map_len_y + 1)))
		return (-1);
	while (t->map_gen[i])
	{
		if (!(t->map_verif[i] = ft_calloc(sizeof(char), t->map_len_x + 1)))
			return (-1);
		while (t->map_gen[i][++j])
			t->map_verif[i][j] = t->map_gen[i][j];
		while (j < t->map_len_x)
			t->map_verif[i][j++] = 32;
		t->map_verif[i][j] = 0;
		j = -1;
		i++;
	}
	t->map_verif[i] = NULL;
	return (0);
}

static int	contour_map_check(t_info *t)
{
	int	i;

	i = 0;
	if (ft_strnstr(t->map_verif[0], "F", t->map_len_x - 1))
		return (-1);
	while (++i < t->map_len_y - 1)
		if (t->map_verif[i][0] == 'F' || t->map_verif[i][t->map_len_x - 1] ==
			'F')
			return (-1);
	if (ft_strnstr(t->map_verif[t->map_len_y - 1], "F", t->map_len_x - 1))
		return (-1);
	return (0);
}

int			ft_check_map(t_info *info, int fd)
{
	is_file_exist(info);
	info->map_len_y = count_string((char const **)info->map_gen);
	info->map_len_x = max_line_counter(info);
	if (map_resizer(info))
		return (ft_closer(info, fd, -1));
	if (ft_player_poser(info) == -1)
		return (ft_closer(info, fd, -1));
	flood_fill(info);
	if (contour_map_check(info))
		return (ft_closer(info, fd, -1));
	return (ft_closer(info, fd, 0));
}
