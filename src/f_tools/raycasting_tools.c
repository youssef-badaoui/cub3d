/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:43:44 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/09/21 19:17:39 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	create_trigonometric_tables(int narc, t_table *table, int i)
{
	double	angle;
	double	ang_in;
	double	*tan_res;
	double	*sin_res;
	double	*cos_res;

	ang_in = ANG_IN_D * M_PI / 180.0;
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

void	ft_distance(t_ray *ray, double ad, double op, t_table *table)
{
	if (ray->quadrant == 1 || ray->quadrant == 3)
	{
		ray->v_distance = op / table->sin_table[ray->index];
		ray->h_distance = ad / table->cos_table[ray->index];
	}
	else
	{
		ray->v_distance = ad / table->cos_table[ray->index];
		ray->h_distance = op / table->sin_table[ray->index];
	}
}

void	triangle_sides(t_ray *ray, t_position position, t_table *table)
{
	double	opposite;
	double	adjacent;

	if (ray->quadrant == 1)
	{
		opposite = ray->xbound - position.virtual_px;
		adjacent = position.virtual_py - ray->ybound;
	}
	else if (ray->quadrant == 2)
	{
		opposite = ray->ybound - position.virtual_py;
		adjacent = ray->xbound - position.virtual_px;
	}
	else if (ray->quadrant == 3)
	{
		opposite = position.virtual_px - ray->xbound;
		adjacent = ray->ybound - position.virtual_py;
	}
	else
	{
		opposite = position.virtual_py - ray->ybound;
		adjacent = position.virtual_px - ray->xbound;
	}
	ft_distance(ray, adjacent, opposite, table);
}
