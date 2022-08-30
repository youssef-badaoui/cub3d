/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/30 09:59:47 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	update_pov(int keycode, t_data *data)
{
	if(keycode == 124)
		data->position->pov = data->position->pov + 5;
	else if (keycode == 123)
		data->position->pov = data->position->pov - 5;
	if	(data->position->pov < 0)
		data->position->pov += 360;
	else if(data->position->pov > 360)
		data->position->pov -= 360;
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
	get_texters(&data);
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
