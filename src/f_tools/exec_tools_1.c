/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:17 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/11 11:09:19 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	init_player_position(t_map *map, t_position *pp)
{
	int	v;

	v = map->pv;
	pp->x_cell = map->px;
	pp->y_cell = map->py;
	pp->virtual_px = pp->x_cell * CELL_SIZE + CELL_SIZE / 2;
	pp->virtual_py = pp->y_cell * CELL_SIZE + CELL_SIZE / 2;
	if (v == 'N')
		pp->pov = N;
	else if (v == 'E')
		pp->pov = E;
	else if (v == 'S')
		pp->pov = S;
	else if (v == 'W')
		pp->pov = W;
	pp->map = map;
}

void	full_data(t_data *data, t_table *table,
	t_position *position, t_ray *ray)
{
	data->table = table;
	data->ray = ray;
	data->position = position;
	data->ray_h = 0;
}

void	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
}

void	get_texters_suit(t_data *data)
{
	t_texters	*t;

	t = &data->mlx->texters;
	t->c_door.img = mlx_xpm_file_to_image(data->mlx->mlx,
			"./wall_texters/code.xpm", &t->c_door.x, &t->c_door.y);
	t->c_door.addr = (int *)mlx_get_data_addr(t->c_door.img,
			&t->c_door.bits_per_pixel, &t->c_door.line_length,
			&t->c_door.endian);
	t->o_door.img = mlx_xpm_file_to_image(data->mlx->mlx,
			"./wall_texters/ooo.xpm", &t->o_door.x, &t->o_door.y);
	t->o_door.addr = (int *)mlx_get_data_addr(t->o_door.img,
			&t->o_door.bits_per_pixel, &t->o_door.line_length,
			&t->o_door.endian);
	t->fog.img = mlx_xpm_file_to_image(data->mlx->mlx,
			"./wall_texters/fog.xpm", &t->fog.x, &t->fog.y);
	t->fog.addr = (int *)mlx_get_data_addr(t->fog.img,
			&t->fog.bits_per_pixel, &t->fog.line_length, &t->fog.endian);
	t->side.img = mlx_xpm_file_to_image(data->mlx->mlx,
			"./wall_texters/side.xpm", &t->side.x, &t->side.y);
	t->side.addr = (int *)mlx_get_data_addr(t->side.img,
			&t->side.bits_per_pixel, &t->side.line_length, &t->side.endian);
	t->nt.img = mlx_xpm_file_to_image(data->mlx->mlx,
			"./wall_texters/nt.xpm", &t->nt.x, &t->nt.y);
	t->nt.addr = (int *)mlx_get_data_addr(t->nt.img,
			&t->nt.bits_per_pixel, &t->nt.line_length, &t->nt.endian);
}

void	get_texters(t_data *data)
{
	t_texters	*t;

	t = &data->mlx->texters;
	t->n_img.img = mlx_xpm_file_to_image(data->mlx->mlx,
			data->map->meta_data[0], &t->n_img.x, &t->n_img.y);
	t->n_img.addr = (int *)mlx_get_data_addr(t->n_img.img,
			&t->n_img.bits_per_pixel, &t->n_img.line_length, &t->n_img.endian);
	t->s_img.img = mlx_xpm_file_to_image(data->mlx->mlx,
			data->map->meta_data[1], &t->s_img.x, &t->s_img.y);
	t->s_img.addr = (int *)mlx_get_data_addr(t->s_img.img,
			&t->s_img.bits_per_pixel, &t->s_img.line_length, &t->s_img.endian);
	t->w_img.img = mlx_xpm_file_to_image(data->mlx->mlx,
			data->map->meta_data[2], &t->w_img.x, &t->w_img.y);
	t->w_img.addr = (int *)mlx_get_data_addr(t->w_img.img,
			&t->w_img.bits_per_pixel, &t->w_img.line_length, &t->w_img.endian);
	t->e_img.img = mlx_xpm_file_to_image(data->mlx->mlx,
			data->map->meta_data[3], &t->e_img.x, &t->e_img.y);
	t->e_img.addr = (int *)mlx_get_data_addr(t->e_img.img,
			&t->e_img.bits_per_pixel, &t->e_img.line_length, &t->e_img.endian);
	t->c_door.img = mlx_xpm_file_to_image(data->mlx->mlx,
			"./wall_texters/code.xpm", &t->c_door.x, &t->c_door.y);
	t->c_door.addr = (int *)mlx_get_data_addr(t->c_door.img,
			&t->c_door.bits_per_pixel, &t->c_door.line_length,
			&t->c_door.endian);
	get_texters_suit(data);
}
