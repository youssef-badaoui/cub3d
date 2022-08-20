/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:49:07 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/20 12:04:05 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

double	calcul_ray_pov(t_position position, int ray)
{
	double	ray_pov;
	double	frif;	//first ray in fov

	frif = position.pov - 30;
	ray_pov = frif + ray * ANG_IN_D;
	if (ray_pov >= 360)
		ray_pov = ray_pov - 360;
	else if (ray_pov < 0)
		ray_pov = ray_pov + 360;
	return (ray_pov);
}

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
	if (position.map->map_tab[xcell_h][ycell_h] == '1')
		ray->h_hit = INTERSECTION_FOUND;
	if (position.map->map_tab[xcell_v][ycell_v] == '1')
		ray->v_hit = INTERSECTION_FOUND;
	if (ray->v_hit || ray->v_hit)
		return (INTERSECTION_FOUND);
	return (0);
}

void	calcul_first_vertical(t_table *table, t_ray *ray, t_position position)
{
	double	diff;

	diff = position.virtual_py;
	if (ray->ray_pov < 180 && ray->ray_pov >= 0)
	{
		ray->xbound = CELL_SIZE * position.x_cell;
		ray->x_step = CELL_SIZE;
		ray->yi = ((ray->xbound - position.virtual_px) / table->tan_table[ray->index]);
	}
	else
	{
		ray->xbound = CELL_SIZE * (position.x_cell - 1);
		ray->x_step = CELL_SIZE * -1;	
		ray->yi = ((position.virtual_px - ray->xbound) / table->tan_table[ray->index]);
	}
	if (ray->quadrant == 4 || ray->quadrant == 1)
		ray->yi = diff - ray->yi;
	else
		ray->yi = diff + ray->yi;
}

void	calcul_first_horizontal(t_table *table, t_ray *ray, t_position position)
{
	double	diff;

	diff = position.virtual_px;
	if (ray->ray_pov > 270 || ray->ray_pov <= 90)
	{
		ray->y_step = CELL_SIZE * -1;
		ray->ybound = (position.y_cell - 1) * CELL_SIZE;
		ray->xi = ((position.virtual_py - ray->ybound) * table->tan_table[ray->index]);
	}
	else
	{
		ray->y_step = CELL_SIZE;
		ray->ybound = position.y_cell * CELL_SIZE;
		ray->xi = ((ray->ybound - position.virtual_py) * table->tan_table[ray->index]);
	}
	if (ray->quadrant == 3 || ray->quadrant == 4)
		ray->xi = diff - ray->xi;
	else
		ray->xi = diff + ray->xi;
	ray->xi += diff;
}

void	calcul_distance(t_table *table, t_ray *ray)
{
	ray->h_distance = ray->xbound / table->sin_table[ray->index];
	ray->v_distance = ray->ybound / table->cos_table[ray->index];
}

void	send_ray(t_table *table, t_ray *ray, t_position position)
{
	int	inter;

	inter = 0;
	while (inter != INTERSECTION_FOUND)
	{
		inter = check_cell_type(ray, position);
		if (inter == INTERSECTION_FOUND)
			calcul_distance(table, ray);
		ray->xbound += ray->x_step;
		ray->ybound += ray->y_step;
		ray->xi = ((ray->ybound - position.virtual_py) * table->tan_table[ray->index]) \
			+ position.virtual_px;
		ray->yi = ((ray->xbound - position.virtual_px) / table->tan_table[ray->index]) \
		+ position.virtual_py;
	}
}

int	calcul_ray_angle(t_ray *ray, double ray_pov)
{
	int		index;
	double	ray_angle;

	ray_angle = ray_pov;
	ray->quadrant = 1;
	if (ray_pov >= 90 && ray_pov < 180)
	{
		ray->quadrant = 2;
		ray_angle = ray_pov - 90.0;
	}
	else if (ray_pov >= 180 && ray_pov < 270)
	{
		ray->quadrant = 3;
		ray_angle = ray_pov - 180.0;
	}
	else if (ray_pov >= 270 && ray_pov < 360)
	{
		ray->quadrant = 4;
		ray_angle = ray_pov - 270.0;
	}
	index = ray_angle / ANG_IN_D;
	return (index);
}

void	casting_rays(t_table *table, t_ray *rays, t_position position)
{
	int	i;

	i = 1;
	printf("(%d, %d) --> (%d, %d) <%lf>\n", position.x_cell, position.y_cell, position.virtual_px, position.virtual_py, position.pov);
	while (i < N_RAY)
	{
		rays[i].ray_pov = calcul_ray_pov(position, i);
		rays[i].index = calcul_ray_angle(&rays[i], rays[i].ray_pov);
		calcul_first_vertical(table, &rays[i], position);
		calcul_first_horizontal(table, &rays[i], position);
		printf("ray pov: %lf\nxi: %lf\nybound: %lf\ny_step: %lf\nxpound: %lf\nyi: %lf\nx_step: %lf\n", 
			rays[i].ray_pov, rays[i].xi, rays[i].ybound, rays[i].y_step, rays[i].xbound, rays[i].yi, rays[i].x_step);
		// rays[i].h_hit = 0;
		// rays[i].v_hit = 0;
		// send_ray(table, &rays[i], position);
		i++;
	}
}