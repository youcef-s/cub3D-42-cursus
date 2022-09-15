/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:29:19 by yachehbo          #+#    #+#             */
/*   Updated: 2022/09/15 18:44:00 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	init the direction that the player looks towards,
**	based on the circle trigonometry.
*/

void	init_player_dir(t_mlx *mlx, int x, int y)
{
	if (mlx->file->scene[x][y] == 'N')
		mlx->player->player_dir = 3 * M_PI_2;
	else if (mlx->file->scene[x][y] == 'S')
		mlx->player->player_dir = M_PI_2;
	else if (mlx->file->scene[x][y] == 'W')
		mlx->player->player_dir = M_PI;
	else if (mlx->file->scene[x][y] == 'E')
		mlx->player->player_dir = 0;
}

/*
**	search for the player and save its coordinates.
**	dx_pos and dy_pos are used to position the player to the middle of the block.
*/

void	init_player(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (mlx->file->scene[i])
	{
		j = 0;
		while (mlx->file->scene[i][j])
		{
			if (ft_strchr("WSNE", mlx->file->scene[i][j]))
			{
				mlx->player->x_pos = j;
				mlx->player->dx_pos = (double)j + 0.5;
				mlx->player->y_pos = i;
				mlx->player->dy_pos = (double)i + 0.5;
				init_player_dir(mlx, i, j);
			}
			j++;
		}
		i++;
	}
	init_press_var(mlx->player);
}

/*
**	The mlx_xpm_file_to_image(); will allow you to read xpm files directly into an image object,
**	and return NULL if it failed or a pointer that will be used later.
**	The mlx_get_data_addr will get the address of the image.
*/

int	txt_adr_ptr(t_mlx *mlx, char *path, int dir)
{
	mlx->txt[dir].txt_ptr = mlx_xpm_file_to_image(mlx->init_ptr,
			path, &mlx->txt[dir].w, &mlx->txt[dir].h);
	if (!mlx->txt[dir].txt_ptr)
		return (1);
	mlx->txt[dir].txt_adr = mlx_get_data_addr(mlx->txt[dir].txt_ptr,
			&mlx->txt[dir].bpp, &mlx->txt[dir].len, &mlx->txt[dir].endian);
	if (!mlx->txt[dir].txt_adr)
		return (1);
	return (0);
}

int	init_txt(t_mlx *mlx)
{
	if (txt_adr_ptr(mlx, mlx->file->we, 0))
		return (1);
	else if (txt_adr_ptr(mlx, mlx->file->no, 1))
		return (1);
	else if (txt_adr_ptr(mlx, mlx->file->ea, 2))
		return (1);
	else if (txt_adr_ptr(mlx, mlx->file->so, 3))
		return (1);
	return (0);
}

/*
**  first of all, we need to initialize the connection between our program and the display.
**  mlx_init will create this connection , and return void *  to use it later.
**  mlx_new_window will create a new window on the screen, and return void * to use it later to draw in it;
**  see : https://qst0.github.io/ft_libgfx/man_mlx.html
*/

int	init_mlx(t_mlx *mlx, t_file *file)
{
	mlx->file = file;
	mlx->player = NULL;
	mlx->txt = NULL;
	mlx->win = NULL;
	mlx->ray = NULL;
	mlx->init_ptr = mlx_init();
	if (!mlx->init_ptr)
		return (1);
	if (struct_allocation(mlx))
		return (1);
	init_player(mlx);
	if (init_txt(mlx))
		return (1);
	mlx->win = mlx_new_window(mlx->init_ptr, WIN_W, WIN_H, "Cub3D");
	if (!mlx->win)
		return (1);
	return (0);
}
