/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:47:32 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/22 15:47:57 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"


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
				ft_color_image(data->mlx,  0x7b7d7d  , i, j);
			else if	(data->map->map_tab[i][j] == '0' || data->map->map_tab[i][j] == 'N')
				ft_color_image(data->mlx,   0x58d68d , i, j);
			j++;
		}
		i++;
	}
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
	printf("drawing start!\n");
	ft_draw_map(data);
	while(i < N_RAY)
	{
		ft_draw_ray(data, i);
		i++;
	}
	ft_mlx_put_px(&mlx , data->position->virtual_px, data->position->virtual_py, 0x0);
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
		{
			if(x == 0 || y == 0)
				ft_mlx_put_px(mlx, x + j * CELL_SIZE, i * CELL_SIZE + y++ , 0x0);
			else
				ft_mlx_put_px(mlx, x + j * CELL_SIZE, i * CELL_SIZE + y++ , color);
		}
			
		x++;
	}
}