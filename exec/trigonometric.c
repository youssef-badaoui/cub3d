/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:00:35 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/26 14:37:54 by ybadaoui         ###   ########.fr       */
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

double	calcul_adjacent(double hypotenuse, double opposite)
{
	double	adjacent;

	adjacent = opposite / hypotenuse;
	return (adjacent);	
}

double	calcul_opposite(double hypotenus, double adjacent)
{
	double	opposite;

	opposite = hypotenus * adjacent;
	return (opposite);
}

void	triangle_sides(t_ray *ray, t_position position, t_table *table)
{
	double	opposite;
	double	adjacent;

	if (ray->quadrant == 1)
	{
		opposite = ray->xbound - position.virtual_px; // x
		adjacent = position.virtual_py - ray->ybound; // y
	}
	else if (ray->quadrant == 2)
	{
		opposite = ray->ybound - position.virtual_py; // y
		adjacent = ray->xbound - position.virtual_px; // x
	}
	else if (ray->quadrant == 3)
	{
		opposite = position.virtual_px - ray->xbound; // x
		adjacent = ray->ybound - position.virtual_py; // y
	}
	else if (ray->quadrant == 4)
	{
		opposite = position.virtual_py - ray->ybound; // y
		adjacent = position.virtual_px - ray->xbound; // x
	}
	if (ray->quadrant == 1 || ray->quadrant == 3)
	{
		ray->v_distance = opposite / table->sin_table[ray->index];
		ray->h_distance = adjacent / table->cos_table[ray->index];
	}
	else
	{
		ray->v_distance = adjacent / table->cos_table[ray->index];
		ray->h_distance = opposite / table->sin_table[ray->index];
	}
}
