/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:58 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/11 11:09:19 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	f_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

t_texter	*is_h(t_data *data, int x_cell, int y_cell, int i)
{
	if (data->ray[i].y_save >= data->position->virtual_py)
	{
		if (data->map->map_tab[y_cell - 1][x_cell] == 'O')
			return (&data->mlx->texters.side);
		else
			return (&data->mlx->texters.s_img);
	}
	else
	{
		if (data->map->map_tab[y_cell + 1][x_cell] == 'O')
			return (&data->mlx->texters.side);
		else
			return (&data->mlx->texters.n_img);
	}
}

t_texter	*is_v(t_data *data, int x_cell, int y_cell, int i)
{
	if (data->ray[i].x_save >= data->position->virtual_px)
	{
		if (data->map->map_tab[y_cell][x_cell - 1] == 'O')
			return (&data->mlx->texters.side);
		else
			return (&data->mlx->texters.e_img);
	}
	else
	{
		if (data->map->map_tab[y_cell][x_cell + 1] == 'O')
			return (&data->mlx->texters.side);
		else
			return (&data->mlx->texters.w_img);
	}
}

t_texter	*get_texter(t_data *data, int i)
{
	int	x_cell;
	int	y_cell;

	x_cell = data->ray[i].x_save / CELL_SIZE;
	y_cell = data->ray[i].y_save / CELL_SIZE;
	if (data->ray[i].ray_pov >= 180 && data->ray[i].first == 'v')
		x_cell -= 1;
	if ((data->ray[i].ray_pov <= 90 || data->ray[i].ray_pov > 270)
		&& data->ray[i].first == 'h')
		y_cell -= 1;
	if (data->ray[i].door == DOOR_FOUND)
		return (&data->mlx->texters.c_door);
	if (data->ray[i].first == 'h')
		return (is_h(data, x_cell, y_cell, i));
	else
		return (is_v(data, x_cell, y_cell, i));
}
