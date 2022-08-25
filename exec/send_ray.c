/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:47:04 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/25 15:42:58 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	check_skip(t_ray *ray, t_position position)
{
	if (ray->xcell_h > position.map->map_w || ray->ycell_h > position.map->map_h)
		ray->h_skip = 1;
	if (ray->xcell_v > position.map->map_w || ray->ycell_v > position.map->map_h)
		ray->v_skip = 1;
	if (ray->quadrant == 4)
	{
		if (ray->xcell_h > position.x_cell || ray->ycell_h > position.y_cell || ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
			
		if (ray->xcell_v > position.x_cell || ray->ycell_v > position.y_cell || ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	else if (ray->quadrant == 1)
	{
		if (ray->xcell_h < position.x_cell || ray->ycell_h > position.y_cell || ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;

		if (ray->xcell_v < position.x_cell || ray->ycell_v > position.y_cell || ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	else if (ray->quadrant == 2)
	{
		if (ray->xcell_h < position.x_cell || ray->ycell_h < position.y_cell || ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
		if (ray->xcell_v < position.x_cell || ray->ycell_v < position.y_cell || ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	else if (ray->quadrant == 3)
	{
		if (ray->xcell_h > position.x_cell || ray->ycell_h < position.y_cell || ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
			
		if (ray->xcell_v > position.x_cell || ray->ycell_v < position.y_cell || ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
}

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

int	check_cell_type(t_ray *ray, t_position position)
{
	calcul_cells(ray);
	check_skip(ray, position);
	printf("hoho1\n");
	// printf("cv (%d, %d) ch (%d, %d) \n", ray->xcell_v, ray->ycell_v, ray->xcell_h, ray->ycell_h);
	if (!(ray->h_skip) && position.map->map_tab[ray->ycell_h][ray->xcell_h] == '1')
	{
		printf("h hit\n");
		ray->h_hit = INTERSECTION_FOUND;
	}
	printf("hoho2\n");
	if (!(ray->v_skip) && position.map->map_tab[ray->ycell_v][ray->xcell_v] == '1')
	{
		printf("v hit\n");
		ray->v_hit = INTERSECTION_FOUND;
	}
	printf("hoho3\n");
	if (ray->v_hit && ray->h_hit)
		return (INTERSECTION_FOUND);
	else if (ray->h_hit && ray->v_skip)
		return (INTERSECTION_FOUND);
	else if (ray->v_hit && ray->h_skip)
		return (INTERSECTION_FOUND);
	printf("hoho4\n");
	return (0);
}

void	calcul_distance(t_table *table, t_ray *ray, t_position position)
{
	triangle_sides(ray, position, table);
	if ((ray->h_distance < ray->v_distance || ray->v_skip) && !(ray->h_skip))
	{
		printf("we go for the horizontal\n");
		ray->x_save = ray->xi;
		ray->y_save = ray->ybound;
	}
	else
	{
		printf("we go for the vertical\n");
		ray->x_save = ray->xbound;
		ray->y_save = ray->yi;
	}
}

void	calcul_next_v_inter(t_table *table, t_ray *ray, t_position position)
{
	double	xside;
	
	xside = 0;
	if (ray->ray_pov <= 180 || ray->ray_pov > 0)
		xside = ray->xbound - position.virtual_px;
	else
		xside = position.virtual_px - ray->xbound;
	if (ray->quadrant == 1 || ray->quadrant == 3)
	{
		ray->yi = calcul_adjacent(table->tan_table[ray->index], xside);
	}
	else
	{
		ray->yi = calcul_opposite(table->tan_table[ray->index], xside);
	}
	if (ray->quadrant == 4 || ray->quadrant == 1)
		ray->yi = position.virtual_py - ray->yi;
	else
		ray->yi = position.virtual_py + ray->yi;
}

void	calcul_next_h_inter(t_table *table, t_ray *ray, t_position position)
{
	double	yside;
	
	yside = 0;
	if (ray->ray_pov > 270 || ray->ray_pov <= 90)
		yside = position.virtual_py - ray->ybound;
	else
		yside = ray->ybound - position.virtual_py;
	if (ray->quadrant == 1 || ray->quadrant == 3)
	{
		ray->xi = calcul_opposite(table->tan_table[ray->index], yside);
	}
	else
	{
		ray->xi = calcul_adjacent(table->tan_table[ray->index], yside);
	}
	if (ray->quadrant == 3 || ray->quadrant == 4)
		ray->xi = position.virtual_px - ray->xi;
	else
		ray->xi = position.virtual_px + ray->xi;
}

void	send_ray(t_table *table, t_ray *ray, t_position position)
{
	int	inter;

	inter = 0;
	while (1)
	{
		printf("-----------sc--------------\n");
		inter = check_cell_type(ray, position);
		printf("-----------ec--------------\n");
		if (inter == INTERSECTION_FOUND)
		{
			return (calcul_distance(table, ray, position));
		}
		if (!(ray->v_hit) && !(ray->v_skip))
		{
			ray->xbound += ray->x_step;
			printf("calculing v\n");
			calcul_next_v_inter(table, ray, position);
		}
		if (!(ray->h_hit) && !(ray->h_skip))
		{
			ray->ybound += ray->y_step;
			printf("calculing h\n");
			calcul_next_h_inter(table, ray, position);
		}
		printf("ray pov: %lf (%d)[%d]\nxi: %lf ybound: %lf y_step: %lf\n\nxpound: %lf yi: %lf x_step: %lf\n", 
			ray->ray_pov, ray->quadrant, ray->index, ray->xi, ray->ybound, ray->y_step, ray->xbound, ray->yi, ray->x_step);
	}
}