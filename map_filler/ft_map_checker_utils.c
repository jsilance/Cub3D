/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:24:16 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 16:16:32 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int			window_size_cor(t_info *t, int reso_x, int reso_y, char **ptr)
{
	if (reso_y <= 0 || reso_x <= 0)
	{
		ft_duty_free(t->map_gen, t->map_len_y);
		ft_duty_free(ptr, 2);
		return (-1);
	}
	t->reso_x = (reso_x > 2560) ? 2560 : reso_x;
	t->reso_y = (reso_y > 1440) ? 1440 : reso_y;
	ft_duty_free(ptr, 2);
	return (0);
}

int			count_string(char const **ptr)
{
	int	count;

	count = 0;
	while (ptr && *ptr++)
		count++;
	return (count);
}

int			ft_strrnstr(char *str, char *needle, int n)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(needle) - 1;
	if (!str || !needle)
		return (-1);
	while (n--)
		if (str[i--] != needle[j--])
			return (-1);
	return (0);
}

static void	f_fill(t_info *t, t_point size, t_point begin)
{
	if (begin.y < 0 || begin.x < 0 || begin.y >= size.y || begin.x >= size.x)
		return ;
	if (t->map_verif[begin.y][begin.x] == 'F' ||
		t->map_verif[begin.y][begin.x] == '1')
		return ;
	t->map_verif[begin.y][begin.x] = 'F';
	begin.x -= 1;
	f_fill(t, size, begin);
	begin.x += 2;
	f_fill(t, size, begin);
	begin.x -= 1;
	begin.y -= 1;
	f_fill(t, size, begin);
	begin.y += 2;
	f_fill(t, size, begin);
}

void		flood_fill(t_info *t)
{
	t_fdfl	info;

	info.begin.x = t->p_pos_x;
	info.begin.y = t->p_pos_y;
	info.size.x = t->map_len_x;
	info.size.y = t->map_len_y;
	f_fill(t, info.size, info.begin);
}
