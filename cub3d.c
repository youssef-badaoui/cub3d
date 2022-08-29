/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/29 09:45:41 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	update_pov(int keycode, t_data *data)
{
	if(keycode == 2)
		data->position->pov = data->position->pov + 5;
	else if (keycode == 0)
		data->position->pov = data->position->pov - 5;
	if	(data->position->pov < 0)
		data->position->pov += 360;
	else if(data->position->pov > 360)
		data->position->pov -= 360;
}

void	ft_line_formula(int	keycode, t_position *position)
{
	position->x_translate = position->virtual_px;
	position->y_translate = position->virtual_py;
	if (keycode == 13)
	{
		position->x_translate += 2 * position->line_key;
		position->y_translate = position->x_translate * position->line_key;
	}
	else if (keycode == 1)
	{
		position->x_translate -= 2 * position->line_key;
		position->y_translate = position->x_translate * position->line_key;
	}
	else if (keycode == 0)
		position->y_translate = position->line_key * position->x_translate + 2;
	else if (keycode == 2)
		position->x_translate = position->y_translate / position->line_key + 2;
	position->x_translate -= position->virtual_px;
	position->y_translate -= position->virtual_py;
}

void	get_pov_index(t_data *data)
{
	int		index;
	double	ray_angle;

	ray_angle = data->position->pov;
	data->position->quadrant = 1;
	if (ray_pov >= 90 && ray_pov < 180)
	{
		data->position->quadrant = 2;
		ray_angle = ray_pov - 90.0;
	}
	else if (ray_pov >= 180 && ray_pov < 270)
	{
		data->position->quadrant = 3;
		ray_angle = ray_pov - 180.0;
	}
	else if (ray_pov >= 270 && ray_pov < 360)
	{
		data->position->quadrant = 4;
		ray_angle = ray_pov - 270.0;
	}
	data->position->pov_index = ray_angle / ANG_IN_D;
}

void	update_position(int keycode, t_data *data)
{
	get_pov_index(data);
	ft_line_formula(keycode, data->position);
	if (data->position->quadrant == 1)
	{
		data->position->virtual_px += data->position->x_translate;
		data->position->virtual_py -= data->position->y_translate;
	}
	else if (data->position->quadrant == 2)
	{
		data->position->virtual_px += data->position->x_translate;
		data->position->virtual_py += data->position->y_translate;
	}
	else if (data->position->quadrant == 3)
	{
		data->position->virtual_px -= data->position->x_translate;
		data->position->virtual_py += data->position->y_translate;
	}
	else if (data->position->quadrant == 4)
	{
		data->position->virtual_px -= data->position->x_translate;
		data->position->virtual_py -= data->position->y_translate;
	}
}

int move_handl( int keycode, t_data *data)
{

	(void) keycode;
	// update_position();
	update_pov(keycode, data);
	drawing(data);
	return 0;
}
int start_exec(t_map *map)
{
	t_table 	table;
	t_position	position;
	t_ray		rays[N_RAY];
	t_data		data;
	t_mlx		mlx;

	full_data(&data, &table, &position, rays);
	data.map = map;
	data.mlx = &mlx;
	create_trigonometric_tables(6480, &table);
	init_player_position(map, &position);
	data.mlx = &mlx;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "call of duty");
	mlx.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	drawing(&data);
	mlx_hook(mlx.win, 02, 00, &move_handl, &data);
	mlx_loop(data.mlx->mlx);
	return (1);
}

int main(int ac, char **av)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if(!init_map(av, ac, map))
		return (0);
	if(!check_and_stor(ac, av, map))
		return (ft_print("-------->$ ERROR: Error While Parsing\n+++NOTE: check map and try again....\n"), 0);
	ft_print("parsing: OK\n");
	start_exec(map);
	return (1);
}
