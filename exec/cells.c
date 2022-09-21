/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cells.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:50:24 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/09/21 18:54:38 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	calcul_cells(t_ray *ray)
{
	ray->xcell_v = ray->xbound / CELL_SIZE;
	ray->ycell_v = ray->yi / CELL_SIZE;
	ray->ycell_h = ray->ybound / CELL_SIZE;
	ray->xcell_h = ray->xi / CELL_SIZE;
	if (ray->ray_pov >= 180 && ray->ray_pov < 360)
		ray->xcell_v -= 1;
	if (ray->ray_pov <= 90 || ray->ray_pov > 270)
		ray->ycell_h -= 1;
}

void	check_border(t_ray *ray, t_position position)
{
	if (!(ray->h_skip)
		&& ray->xcell_h >= ft_strlen(position.map->map_tab[ray->ycell_h]))
		ray->h_skip = 1;
	if (!(ray->v_skip)
		&& ray->xcell_v >= ft_strlen(position.map->map_tab[ray->ycell_v]))
		ray->v_skip = 1;
}

void	check_skip_second(t_ray *ray, t_position position)
{
	if (ray->quadrant == 2)
	{
		if (ray->xcell_h < position.x_cell || ray->ycell_h < position.y_cell
			|| ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
		if (ray->xcell_v < position.x_cell || ray->ycell_v < position.y_cell
			|| ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	else if (ray->quadrant == 3)
	{
		if (ray->xcell_h > position.x_cell || ray->ycell_h < position.y_cell
			|| ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
		if (ray->xcell_v > position.x_cell || ray->ycell_v < position.y_cell
			|| ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	check_border(ray, position);
}

void	check_skip(t_ray *ray, t_position position)
{
	if (ray->xcell_h >= position.map->map_w
		|| ray->ycell_h >= position.map->map_h)
		ray->h_skip = 1;
	if (ray->xcell_v >= position.map->map_w
		|| ray->ycell_v >= position.map->map_h)
		ray->v_skip = 1;
	if (ray->quadrant == 4)
	{
		if (ray->xcell_h > position.x_cell || ray->ycell_h > position.y_cell
			|| ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
		if (ray->xcell_v > position.x_cell || ray->ycell_v > position.y_cell
			|| ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	else if (ray->quadrant == 1)
	{
		if (ray->xcell_h < position.x_cell || ray->ycell_h > position.y_cell
			|| ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
		if (ray->xcell_v < position.x_cell || ray->ycell_v > position.y_cell
			|| ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	check_skip_second(ray, position);
}
