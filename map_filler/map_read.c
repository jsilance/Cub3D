/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:14:36 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 19:37:58 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	ft_closer(int fd, int ret)
{
	close(fd);
	return (ret);
}

static int	cotoi(char *line, t_info *t)
{
	int	ret;

	if (ft_charcount(line, ',') > 2)
		ft_error(3, -1, t, 0);
	ret = ft_atoi(line) * 65536;
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	else
		ft_error(3, -1, t, 0);
	ret += ft_atoi(line) * 256;
	while (ft_isdigit(*line))
		line++;
	line++;
	ret += ft_atoi(line);
	return (ret);
}

static char	*ft_mapdup(const char *s)
{
	char	*ptr;

	if (!(ptr = malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	if (s)
		ft_memcpy(ptr, s, ft_strlen(s));
	ptr[ft_strlen(s)] = '\0';
	return ((char *)ptr);
}

void		info_part_one(t_info *info, char *line)
{
	char	**ptr;

	if (line[0] == 'R')
	{
		ptr = ft_split(&line[2], ' ');
		if (window_size_cor(info, ft_atoi(ptr[0]), ft_atoi(ptr[1]), ptr))
			ft_error(1, -1, info, 0);
	}
	else if (line[0] == 'S')
	{
		if (line[1] == ' ')
			info->texture_sprite = ft_strdup(&line[2]);
		else if (line[1 == 'O'])
			info->texture_south = ft_strdup(&line[3]);
	}
	else if (!ft_strncmp(&line[0], "NO ", 3))
		info->texture_north = ft_strdup(&line[3]);
	else if (!ft_strncmp(&line[0], "EA ", 3))
		info->texture_east = ft_strdup(&line[3]);
	else if (!ft_strncmp(&line[0], "WE ", 3))
		info->texture_west = ft_strdup(&line[3]);
	else if (line[0] == 'F')
		info->color_ground = cotoi(&line[2], info);
	else if (line[0] == 'C')
		info->color_roof = cotoi(&line[2], info);
}

int			ft_map_read(t_info *t)
{
	char	*line;
	int		fd;

	if (ft_strrnstr(t->map_file, ".cub", 4))
		return (-1);
	fd = open(t->map_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = NULL;
	if (ft_parsing(t, line, fd, 0) == -1)
		return (ft_closer(fd, -1));
	return (ft_check_map(t, fd));
}
