/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:58:31 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/25 20:26:22 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define TEST test(info);
# define TEST_m test(&info);
# define TEST_R aff_r(info);

# include "minilibx_opengl/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <math.h>

# include <stdio.h>

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef	struct	s_fdfl
{
	t_point	size;
	t_point	begin;
}				t_fdfl;

typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct	s_sprite
{
	double	s_sptdist;
	double	sprite_x;
	double	sprite_y;
	double	invdet;
	double	trans_x;
	double	trans_y;

	int		s_screen_x;
	int		s_height;
	int		s_width;
	int		stripe;
	int		color;

	int		i_drawstart_x;
	int		i_drawend_x;
	int		i_drawstart_y;
	int		i_drawend_y;
}				t_sprite;


typedef struct	s_info
{
	int		reso_x;
	int		reso_y;
	void	*mlx_ptr;
	void	*window_ptr;

	int		color_roof;
	int		color_ground;

	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	char	*texture_sprite;
	t_data	tex_f[5];
	int		texture_size_x;
	int		texture_size_y;
	int		map_total_flags;
	
	char	*map_file;
	char	**map_gen;
	char	**map_verif;
	int		map_len_x;
	int		map_len_y;
	
	double	p_pos_x;
	double	p_pos_y;
	char	p_sp_face;
	double	p_look_x;
	double	p_look_y;
	double	p_move_speed;
	double	p_rot_speed;
		
	double	w_plane_x;
	double	w_plane_y;
	double	w_cam_x;
	double	w_cam_y;

	int		i_line_height;
	int		i_draw_start;
	int		i_draw_end;
	void	*i_img;
	int		*i_addr;
	int		i_bpp;
	int		i_sl;
	int		i_endian;
	
	double	t_texpos;
	double	t_step;
	int		t_texx;
	int		t_texy;
	int		t_width;
	int		t_height;
	int		t_texnum;
	
	double	r_ray_dir_x;
	double	r_ray_dir_y;
	double	r_ray_pos_x;
	double	r_ray_pos_y;
	int		r_map_x;
	int		r_map_y;
	double	r_side_dist_x;
	double	r_side_dist_y;
	double	r_delta_dist_x;
	double	r_delta_dist_y;
	double	r_perp_wall_dist;
	int		r_step_x;
	int		r_step_y;
	int		r_hit;
	int		r_side;
	
	double	time;
	double	old_time;

	int		i_screenshot;
	int		pa_ismap;

	double	s_pos_x;
	double	s_pos_y;
	t_sprite	s;
}				t_info;

int		key_pressed(int key, void *params);
void	exit_hook(void *params);
int		win_full_color(int x, t_info *t_info, int color, int start_p);
int		ver_line_color(int x, t_info *info, int color, int fs);
int		window_event(int key, void *params);
	
void	struct_init(t_info *info);
int		map_read(t_info *info);
char	**ft_realloc_d_malloc(char **ptr, char *str, t_info *info);
void	flood_fill(t_info *t);
void	ft_duty_free(char **ptr_ptr, int string);
double	ft_abs(double nbr);

int		ft_check_map(t_info *info, int fd);
int		str_char_count(char *tab);
void	ft_map_inter(t_info *info);
int		ft_player_poser(t_info *info);
	
int		ft_rays(t_info *info);
void	side_dist_calc(t_info *t);
int		max_shadow(int color, unsigned int m);
int		rgb_shadow(int pixel_color, int fs);

int		*get_pixel_color(t_data *data, int x, int y);
void	texture_init(t_info *t);
int		sprite_casting(t_info *t, double zbuf[t->reso_x], int y);

void	bmp_maker(t_info *t);

int		count_string(char const **ptr);
int		ft_strrnstr(char *str, char *needle, int n);
int		window_size_cor(t_info *t, int reso_x, int reso_y, char **ptr);
void	ft_error(int type, int exit_code, t_info *t, int flg);
void	is_file_exist(t_info *info);
int		ft_parsing(t_info *t, char *line, int fd, int i);
void	info_part_one(t_info *info, char *line);

#endif
