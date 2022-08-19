/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:49:07 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/19 11:40:17 by Ma3ert           ###   ########.fr       */
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

void	calcul_first_inter(t_table *table, t_ray *ray, t_position position)
{
	if (ray->ray_pov < 180 && ray->ray_pov >= 0)
	{
		ray->xbound = CELL_SIZE * position.x_cell;
		ray->x_step = CELL_SIZE;
	}
	else
	{
		ray->xbound = CELL_SIZE * (position.x_cell - 1);
		ray->x_step = CELL_SIZE * -1;	
	}
	ray->yi = ((ray->xbound - position.virtual_px) / table->tan_table[ray->index]) \
	 + position.virtual_py;
	if (ray->ray_pov > 270 || ray->ray_pov <= 90)
	{
		ray->y_step = CELL_SIZE * -1;
		ray->ybound = (position.y_cell - 1) * CELL_SIZE;
	}
	else
	{
		ray->y_step = CELL_SIZE;
		ray->ybound = position.y_cell * CELL_SIZE;
	}
	ray->xi = ((ray->ybound - position.virtual_py) * table->tan_table[ray->index]) \
		+ position.virtual_px;
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

void	casting_rays(t_table *table, t_ray *rays, t_position position)
{
	int	i;

	i = 1;
	while (i < N_RAY)
	{
		rays[i].index = i;
		rays[i].ray_pov = calcul_ray_pov(position, i);
		calcul_first_inter(table, &rays[i], position);
		rays[i].h_hit = 0;
		rays[i].v_hit = 0;
		send_ray(table, &rays[i], position);
		i++;
	}
}