/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:00:35 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/19 12:19:54 by ybadaoui         ###   ########.fr       */
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
				ft_color_image(data->mlx, 0xFFFFFFF, i, j);
			else if	(data->map->map_tab[i][j] == '0'|| data->map->map_tab[i][j] == 'N')
				ft_color_image(data->mlx, 0xa32424, i, j);
			j++;
		}
		i++;
	}
	printf("%d    %d\n", data->position->virtual_px, data->position->virtual_py);
	// ft_mlx_put_px(&data->mlx->mlx, data->position->virtual_px, data->position->virtual_py, 0x0);
}

void drawing(t_data *data)
{
	t_mlx mlx;
	int i;
	
	i = 0;
	data->mlx = &mlx;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, (data->map->map_w - 1) * CELL_SIZE, data->map->map_h * CELL_SIZE, "call of duty");
	mlx.img = mlx_new_image(mlx.mlx, (data->map->map_w - 1) * CELL_SIZE, data->map->map_h * CELL_SIZE);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	ft_draw_map(data);
	while(i < 1080)
	{
		// printf("hoooolaaaaaa2!\n");

		 printf("xi = %lf  yi == %lf\n", data->ray[i].xi, data->ray[i].yi);
		 printf("xbound = %lf  ybound == %lf\n", data->ray[i].xbound, data->ray[i].ybound);
		ft_draw_ray(data, i);
		i++;
	}
	
	printf("drawing done!\n");
	mlx_put_image_to_window(data->mlx->mlx,data->mlx->win, data->mlx->img, 0,0);
	mlx_loop(data->mlx->mlx);
}


void	ft_color_image(t_mlx *mlx,  int color, int i , int j)
{
	int x;
	int y;

	x = 0;
	while(x < CELL_SIZE)
	{
		y = 0;
		while(y < CELL_SIZE)
			ft_mlx_put_px(mlx, x + j * CELL_SIZE, i * CELL_SIZE + y++ , color);
		x++;
	}
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