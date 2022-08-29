/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:47:32 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/29 09:45:17 by Ma3ert           ###   ########.fr       */
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
void	ft_3d(t_data *data)
{
	int	i;

	i = 0;
	data->ray_w = WIN_W / N_RAY;
	if(!data->ray_w)
		data->ray_w = 1;
	while(i < N_RAY)
	{
		data->ray[i].save_distance = data->ray[i].save_distance *  data->table->cos_table[abs(1080/2 - i)];
		if(data->ray[i].save_distance/CELL_SIZE)
			data->ray[i].ray_h = WIN_H / (data->ray[i].save_distance/CELL_SIZE);
		if (data->ray[i].ray_h >= WIN_H)
			data->ray[i].ray_h = WIN_H - 1;
		// printf("wall_h = %d\n", data->ray[i].ray_h);
		draw_3d(i, data);
		i++;
	}
}

void drawing(t_data *data)
{
	int i;
	
	i = 0;
	casting_rays(data->table, data->ray, *data->position);
	// printf("drawing start!\n");
	// ft_draw_map(data);
	ft_color_win(data->mlx, 0x0);
	ft_3d(data);
	// ft_mlx_put_px(data->mlx , data->position->virtual_px, data->position->virtual_py, 0x0);
	// printf("drawing done!\n");
	mlx_put_image_to_window(data->mlx->mlx,data->mlx->win, data->mlx->img, 0,0);
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

void	ft_color_win(t_mlx *mlx,  int color)
{
	int x;
	int y;

	color =0;
	x = 0;
	while(x < WIN_W)
	{
		y = 0;
		while(y < WIN_H)
		{
			if(y > WIN_H/2)
				ft_mlx_put_px(mlx, x, y++, 0x298e5f);
			else
				ft_mlx_put_px(mlx, x, y++, 0x4384d7);
				
		}
		x++;
	}
}