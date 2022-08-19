/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:00:35 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/18 15:04:13 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	create_trigonometric_tables(int narc, t_table *table)
{
	int		i;
	double	angle;
	double	ang_in;
	double	*tan_res;
	double	*sin_res;
	double	*cos_res;

	i = 0;
	ang_in = ANG_IN_D * M_PI/180.0;
	tan_res = malloc(sizeof(double) * narc);
	sin_res = malloc(sizeof(double) * narc);
	cos_res = malloc(sizeof(double) * narc);
	while (i < narc)
	{
		angle = i * ang_in;
		tan_res[i] = tan(angle);
		cos_res[i] = cos(angle);
		sin_res[i] = sin(angle);
		i++;
	}
	table->tan_table = tan_res;
	table->cos_table = cos_res;
	table->sin_table = sin_res;
}

int start_exec(t_map *map)
{
	t_table 	table;
	t_position	position;
	t_ray		rays[1080];
	t_data		data;

	full_data(&data, &table, &position, rays);
	data.map = map;
	create_trigonometric_tables(6480, &table);
	init_player_position(map, &position);
	casting_rays(&table, &rays[0], position);
	drawing(&data);
	return (1);
}

void drawing(t_data *data)
{
	t_mlx mlx;
	int i;
	
	i = 0;
	data->mlx = &mlx;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 430, 430, "call of duty");
	mlx.img = mlx_new_image(mlx.mlx, 16, 16);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	ft_draw_map(data);
	mlx_destroy_image(data->mlx, data->mlx->img);
	mlx.img = mlx_new_image(data->mlx, 430, 430);
	while(i < 1080)
		ft_draw_ray(data, i++);
}

void	ft_draw_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while(i < data->map->map_h)
	{
		j = 0;
		while(data->map->map_tab[i][j])
		{
			if(data->map->map_tab[i][j] == '1')
				ft_color_image(data->mlx, 0xFFFFFFF);
			else
				ft_color_image(data->mlx, 0xa32424);
			mlx_put_image_to_window(data->mlx, data->mlx->win, data->mlx->img, j * CELL_SIZE, i * CELL_SIZE);
			j++;
		}
		i++;
	}
}

void	ft_color_image(t_mlx *mlx,  int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(x < 16)
	{
		while(y < 16)
			ft_mlx_put_px(mlx, x, y++, color);
		y++;
	}
}

void	ft_mlx_put_px(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	dst = color;
}

int start_exec(t_map *map)
{
	t_table 	table;
	t_position	position;
	t_ray		rays[1080];
	t_data		data;

	full_data(&data, &table, &position, rays);
	data.map = map;
	create_trigonometric_tables(6480, &table);
	init_player_position(map, &position);
	casting_rays(&table, &rays[0], position);
	drawing(&data);
	return (1);
}