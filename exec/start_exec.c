/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:49:03 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/10/05 10:14:10 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	hooking(t_mlx *mlx, t_data *data)
{
	mlx_hook(mlx->win, 02, 0L, &keypress, data);
	mlx_hook(mlx->win, 03, 0L, &keyrelease, data);
	mlx_hook(mlx->win, 04, 0L, &tir_press, data);
	mlx_hook(mlx->win, 05, 0L, &tir_release, data);
	mlx_hook(mlx->win, 06, 0L, &mouse_move, data);
	mlx_loop_hook(mlx->mlx, &move_handl, data);
	mlx_loop(data->mlx->mlx);
}

void	pre_exec(t_data *data, t_table *table, t_position *position, t_ray *ray)
{
	create_trigonometric_tables(6480, table, 0);
	init_player_position(data->map, position);
	full_data(data, table, position, ray);
}

int	start_exec(t_map *map)
{
	t_table		table;
	t_position	position;
	t_ray		rays[N_RAY];
	t_data		data;
	t_mlx		mlx;

	data.map = map;
	data.mlx = &mlx;
	pre_exec(&data, &table, &position, rays);
	ft_init_mlx(&mlx);
	get_texters(&data);
	init_keystate(&data);
	get_gun(&data);
	drawing(&data);
	hooking(&mlx, &data);
	return (1);
}
