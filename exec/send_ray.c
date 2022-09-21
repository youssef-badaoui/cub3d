/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:20:11 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/09/21 18:36:47 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	calcul_next_h_inter(t_table *table, t_ray *ray, t_position position)
{
	double	yside;

	yside = 0;
	if (ray->ray_pov > 270 || ray->ray_pov <= 90)
		yside = position.virtual_py - ray->ybound;
	else
		yside = ray->ybound - position.virtual_py;
	if (ray->quadrant == 1 || ray->quadrant == 3)
		ray->xi = calcul_opposite(table->tan_table[ray->index], yside);
	else
		ray->xi = calcul_adjacent(table->tan_table[ray->index], yside);
	if (ray->quadrant == 3 || ray->quadrant == 4)
		ray->xi = position.virtual_px - ray->xi;
	else
		ray->xi = position.virtual_px + ray->xi;
}

void	calcul_next_v_inter(t_table *table, t_ray *ray, t_position position)
{
	double	xside;

	xside = 0;
	if (ray->ray_pov <= 180 && ray->ray_pov > 0)
		xside = ray->xbound - position.virtual_px;
	else
		xside = position.virtual_px - ray->xbound;
	if (ray->quadrant == 1 || ray->quadrant == 3)
		ray->yi = calcul_adjacent(table->tan_table[ray->index], xside);
	else
		ray->yi = calcul_opposite(table->tan_table[ray->index], xside);
	if (ray->quadrant == 4 || ray->quadrant == 1)
		ray->yi = position.virtual_py - ray->yi;
	else
		ray->yi = position.virtual_py + ray->yi;
}

void	calcul_distance(t_table *table, t_ray *ray, t_position position)
{
	triangle_sides(ray, position, table);
	if ((ray->h_distance < ray->v_distance || ray->v_skip) && !(ray->h_skip))
	{
		ray->x_save = ray->xi;
		ray->y_save = ray->ybound;
		ray->save_distance = ray->h_distance;
		ray->first = 'h';
		if (position.map->map_tab[ray->ycell_h][ray->xcell_h] == 'C')
			ray->door = DOOR_FOUND;
	}
	else
	{
		ray->x_save = ray->xbound;
		ray->y_save = ray->yi;
		ray->save_distance = ray->v_distance;
		ray->first = 'v';
		if (position.map->map_tab[ray->ycell_v][ray->xcell_v] == 'C')
			ray->door = DOOR_FOUND;
	}
}

int	check_cell_type(t_ray *ray, t_position position)
{
	calcul_cells(ray);
	check_skip(ray, position);
	if (!(ray->h_skip) \
			&& (position.map->map_tab[ray->ycell_h][ray->xcell_h] == '1' || \
			position.map->map_tab[ray->ycell_h][ray->xcell_h] == 'C'))
		ray->h_hit = INTERSECTION_FOUND;
	if ((!(ray->v_skip) && \
			(position.map->map_tab[ray->ycell_v][ray->xcell_v] == '1' || \
			position.map->map_tab[ray->ycell_v][ray->xcell_v] == 'C')))
		ray->v_hit = INTERSECTION_FOUND;
	if (ray->v_hit && ray->h_hit)
		return (INTERSECTION_FOUND);
	if (ray->h_hit && ray->v_skip)
		return (INTERSECTION_FOUND);
	if (ray->v_hit && ray->h_skip)
		return (INTERSECTION_FOUND);
	return (0);
}

void	send_ray(t_table *table, t_ray *ray, t_position position)
{
	int	inter;

	inter = 0;
	while (1)
	{
		inter = check_cell_type(ray, position);
		if (inter == INTERSECTION_FOUND)
			return (calcul_distance(table, ray, position));
		if (!(ray->v_hit) && !(ray->v_skip))
		{
			ray->xbound += ray->x_step;
			calcul_next_v_inter(table, ray, position);
		}
		if (!(ray->h_hit) && !(ray->h_skip))
		{
			ray->ybound += ray->y_step;
			calcul_next_h_inter(table, ray, position);
		}
	}
}
