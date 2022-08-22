/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:47:04 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/22 15:48:47 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"


int	check_cell_type(t_ray *ray, t_position position)
{
	int	xcell_v;
	int	ycell_v;
	int	xcell_h;
	int	ycell_h;

	xcell_v = ray->xbound / CELL_SIZE;
	ycell_v = ray->yi / CELL_SIZE;
	ycell_h = ray->ybound / CELL_SIZE;
	xcell_h = ray->xi / CELL_SIZE;
	if (xcell_h > position.map->map_w || ycell_h > position.map->map_h)
		ray->h_skip = 1;
	if (xcell_v > position.map->map_w || ycell_v > position.map->map_h)
		ray->v_skip = 1;
	printf("cv (%d, %d) ch (%d, %d)\n", xcell_v, ycell_v, xcell_h, ycell_h);
	if (!(ray->h_skip) && position.map->map_tab[ycell_h][xcell_h] == '1')
	{
		printf("horizontal hit\n");
		ray->h_hit = INTERSECTION_FOUND;
	}
	if (!(ray->v_skip) && position.map->map_tab[ycell_v][xcell_v] == '1')
	{
		printf("vertical hit\n");
		ray->v_hit = INTERSECTION_FOUND;
	}
	printf("hoho3\n");
	if (ray->v_hit || ray->v_hit)
	{
		printf("found a hit\n");
		return (INTERSECTION_FOUND);
	}
	printf("//////////////////////////\n");
	return (0);
}

void	calcul_distance(t_table *table, t_ray *ray)
{
	ray->h_distance = ray->xbound / table->sin_table[ray->index];
	ray->v_distance = ray->ybound / table->cos_table[ray->index];
	if (ray->h_distance < ray->v_distance)
	{
		ray->x_save = ray->xbound;
		ray->y_save = ray->yi;
	}
	else
	{
		ray->x_save = ray->xi;
		ray->y_save = ray->ybound;
	}
}

void	calcul_next_inter(t_table *table, t_ray *ray, t_position position)
{
	double	xside;
	double	yside;

	xside = 0;
	yside = 0;
	if (ray->ray_pov > 270 || ray->ray_pov <= 90)
		yside = position.virtual_py - ray->ybound;
	else
		yside = ray->ybound - position.virtual_py;
	if (ray->ray_pov <= 180 || ray->ray_pov > 0)
		xside = ray->xbound - position.virtual_px;
	else
		xside = position.virtual_px - ray->xbound;
	if (ray->quadrant == 1 || ray->quadrant == 3)
	{
		ray->xi = calcul_opposite(table->tan_table[ray->index], yside);
		ray->yi = calcul_adjacent(table->tan_table[ray->index], xside);
	}
	else
	{
		ray->xi = calcul_adjacent(table->tan_table[ray->index], yside);
		ray->yi = calcul_opposite(table->tan_table[ray->index], xside);
	}
	if (ray->quadrant == 3 || ray->quadrant == 4)
		ray->xi = position.virtual_px - ray->xi;
	else
		ray->xi = position.virtual_px + ray->xi;
	if (ray->quadrant == 4 || ray->quadrant == 1)
		ray->yi = position.virtual_py - ray->yi;
	else
		ray->yi = position.virtual_py + ray->yi;
}

void	send_ray(t_table *table, t_ray *ray, t_position position)
{
	int	inter;

	inter = 0;
	while (inter != INTERSECTION_FOUND)
	{
		inter = check_cell_type(ray, position);
		if (inter == INTERSECTION_FOUND)
			return (calcul_distance(table, ray));
		ray->xbound += ray->x_step;
		ray->ybound += ray->y_step;
		calcul_next_inter(table, ray, position);
	}
}