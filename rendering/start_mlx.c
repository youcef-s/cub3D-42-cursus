/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:34:57 by yachehbo          #+#    #+#             */
/*   Updated: 2022/09/15 18:46:32 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	see : https://permadi.com/1996/05/ray-casting-tutorial-10/
*/

int	draw_wall(t_mlx *mlx, t_ray *ray, int y)
{
	int		dirc;
	int		col;
	int		wall_end;
	double	row;
	double	x_step;

	wall_end = (int)((WIN_H + ray->wall_len) / 2);
	dirc = dir_wall(ray);
	col = (int)((ray->hit_x + ray->hit_y) * mlx->txt[dirc].w)
		% mlx->txt[dirc].w;
	row = 0.00;
	x_step = mlx->txt[dirc].h / (double)ray->wall_len;
	while (ray->wall_height < wall_end)
	{
		if (ray->wall_height >= 0 && ray->wall_height < WIN_H)
			pixel_put(mlx, y, ray->wall_height,
				get_txt_color(&mlx->txt[dirc], col, (int)row));
		ray->wall_height++;
		row += x_step;
	}
	return (ray->wall_height);
}

void	draw_column(int x, t_ray *ray, t_mlx *mlx)
{
	int	y;

	y = -1;
	ray->wall_height = (int)((WIN_H - ray->wall_len) / 2);
	while (++y < ray->wall_height)
		pixel_put(mlx, x, y, mlx->file->ceilling);
	y = draw_wall(mlx, ray, x);
	while (y < WIN_H)
	{
		pixel_put(mlx, x, y, mlx->file->floor);
		y++;
	}
}

/*
**	ray_angle is the angle between the x axis and the ray
**	camera_angle is used to treat the fisheye effect
**	ray->wall_len is the height of the projected wall
**	see: https://permadi.com/1996/05/ray-casting-tutorial-8/
**	and https://permadi.com/1996/05/ray-casting-tutorial-9/
*/

int	cast_ray(t_mlx *mlx, t_player *p, t_ray *ray)
{
	int		x;
	double	ray_angle;
	double	camera_angle;

	x = -1 * (WIN_W / 2);
	while (x < (WIN_W / 2))
	{
		ray_angle = p->player_dir + (double)x
			* ((double)FOV / WIN_W) * (M_PI / 180);
		camera_angle = (double)x * ((double)FOV / WIN_W) * (M_PI / 180);
		init_ray(ray, p, ray_angle);
		init_ray_2(ray);
		find_wall(ray, mlx->file);
		ray->wall_len = WIN_H / (ray->r_length * cos(camera_angle));
		draw_column(x + WIN_W / 2, ray, mlx);
		x++;
	}
	return (0);
}

/*
**	mlx_new_image will create a new image in memory, and return a void * needed to manipulate this image later.
**	mlx_get_data_addr will get the addr of the img.
**	mlx_put_image_to_window will put the image in the window.
**	see : https://gontjarow.github.io/MiniLibX/mlx_new_image.html
*/

int	create_image(t_mlx *mlx)
{
	mlx_clear_window(mlx->init_ptr, mlx->win);
	mlx->img = mlx_new_image(mlx->init_ptr, WIN_W, WIN_H);
	if (!mlx->img)
		return (1);
	mlx->addr_img = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl, &mlx->en);
	cast_ray(mlx, mlx->player, mlx->ray);
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
	return (0);
}

/*
**	mlx_hook calls a function when a specific event occurs.
**	mlx_loop_hook is identical to mlx_hook, but the given function will be called when no event occurs.
**  see: https://harm-smits.github.io/42docs/libs/minilibx/hooks.html
*/

int	start_mlx(t_mlx *mlx, t_file *file)
{
	if (init_mlx(mlx, file))
		return (1);
	if (create_image(mlx))
		return (1);
	mlx_hook(mlx->win, 17, 1L << 17, close_win, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, press, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, release, mlx);
	mlx_loop_hook(mlx->init_ptr, update, mlx);
	return (0);
}
