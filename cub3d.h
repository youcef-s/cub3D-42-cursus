/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:04:17 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/09/15 18:40:23 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "mlx.h"
# include "math.h"

/*
**	FOV means field of view
**	a narrow FOV of around 60 degrees is used for console games
*/

# define WIN_W	1080
# define WIN_H	1080
# define FOV	60 
# define SPEED	0.05

typedef struct s_ray
{
	double		p_dx_pos;
	double		p_dy_pos;
	int			p_check_x;
	int			p_check_y;
	double		r_dir_x;
	double		r_dir_y;
	double		r_step_x;
	double		r_step_y;
	double		r_len_x;
	double		r_len_y;
	double		r_length;
	int			increm_x;
	int			increm_y;
	int			wall_hit;
	double		hit_x;
	double		hit_y;
	int			side;
	double		wall_len;
	int			wall_height;
}	t_ray;

typedef struct s_file
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	int		ceilling;
	int		floor;
	int		height;
	t_list	*map;
	char	**scene;
}	t_file;

typedef struct s_player
{
	int		x_pos;
	int		y_pos;
	double	dx_pos;
	double	dy_pos;
	double	player_dir;
	int		up;
	int		down;
	int		left;
	int		right;
	int		rot_left;
	int		rot_right;
}	t_player;

typedef struct s_txt
{
	void	*txt_ptr;
	char	*txt_adr;
	int		w;
	int		h;
	int		bpp;
	int		len;
	int		endian;
}	t_txt;

typedef struct s_mlx
{
	void		*init_ptr;
	void		*win;
	void		*img;
	char		*addr_img;
	int			bpp;
	int			sl;
	int			en;
	t_file		*file;
	t_player	*player;
	t_txt		*txt;
	t_ray		*ray;
}	t_mlx;
/********************parsing*****************/
int		parsing(t_file *file, int ac, char **av);
void	free_2d_array(char **str);
void	free_file(t_file *file);
int		check_first_and_last_line(t_file *file);
int		check_left_wall(t_file *file);
int		check_right_wall(t_file *file);
int		check_middle_lines(t_file *file);
void	init_vars(t_file *file);
int		fill_scene(t_file *file);
int		fill_lst(t_file *file, int fd);
int		fill_ceilling(t_file *file, char c, int color);
int		fill_textures(t_file *file, char **str);
int		check_elements(t_file *file, char **str);
char	**ft_split2(char *str, char *charset);
char	*update_red(char *str);
/*****************start_mlx******************/
int		start_mlx(t_mlx *mlx, t_file *file);
int		create_image(t_mlx *mlx);
int		cast_ray(t_mlx *mlx, t_player *p, t_ray *ray);
void	draw_column(int x, t_ray *ray, t_mlx *mlx);
int		draw_wall(t_mlx *mlx, t_ray *ray, int y);
/*****************init******************/
int		init_mlx(t_mlx *mlx, t_file *file);
int		init_txt(t_mlx *mlx);
int		txt_adr_ptr(t_mlx *mlx, char *path, int dir);
void	init_player(t_mlx *mlx);
void	init_player_dir(t_mlx *mlx, int x, int y);
/*****************ray_init******************/
void	init_ray(t_ray *ray, t_player *player, double ray_angle);
void	init_ray_2(t_ray *ray);
void	find_wall(t_ray *ray, t_file *file);
/*****************utils******************/
int		dir_wall(t_ray *ray);
int		get_txt_color(t_txt *txt, int x, int y);
void	pixel_put(t_mlx *mlx, int x, int y, int color);
int		struct_allocation(t_mlx *mlx);
void	init_press_var(t_player *player);
/*****************hooks******************/
int		release(int key, t_mlx *mlx);
int		press(int key, t_mlx *mlx);
int		close_win(t_mlx *mlx);
/*****************update******************/
void	update_player_pos(t_mlx *mlx);
int		update(void *mlx_v);
/*****************move******************/
void	move_right(t_mlx *mlx);
void	move_left(t_mlx *mlx);
void	move_down(t_mlx *mlx);
void	move_up(t_mlx *mlx);
int		wall_collision(t_mlx *mlx, double x, double y);
/***************free******************/
void	free_all(t_mlx *mlx);
#endif
