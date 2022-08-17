/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:00:35 by Ma3ert            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/17 10:32:47 by Ma3ert           ###   ########.fr       */
=======
/*   Updated: 2022/08/16 15:36:20 by ybadaoui         ###   ########.fr       */
>>>>>>> 6529c364572fedae92acb14b66e4b0659c4bda62
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	create_trigonometric_tables(int narc, t_table *table)
{
	int		i;
	double	angle;
	double	ang_in;
	double	*tan_res;

	i = 0;
	ang_in = ANG_IN_D * M_PI/180.0;
	tan_res = malloc(sizeof(double) * narc);
	while (i < narc)
	{
		angle = i * ang_in;
		tan_res[i] = tan(angle);
		i++;
	}
	table->tan_table = tan_res;
}

void	send_ray(t_table *table, t_ray ray, t_position position)
{
	
}

void	calcul_first_inter(t_table *table, t_ray ray, t_position position)
{
	if (ray.ray_pov < 180 && ray.ray_pov >= 0)
	{
		ray.xpound = CELL_SIZE * position.x_cell;
		ray.yi = table->tan_table[ray.index] * (ray.xpound - position.virtual_px) + position.virtual_py;
	}
	else
	{
		ray.xpound = CELL_SIZE * (position.x_cell - 1);
		ray.yi = table->tan_table[ray.index] * (position.virtual_px - ray.xpound) + position.virtual_py;
	}
	if (ray.ray_pov > 270 || ray.ray_pov <= 90)
		ray.ypound = (position.y_cell - 1) * CELL_SIZE;
	else
		ray.ypound = position.y_cell * CELL_SIZE;
}

double	calcul_ray_pov(t_position position, int ray)
{
	double	ray_pov;
	double	frif;//first ray in fov

	frif = position.pov - 30;
	ray_pov = frif + ray * ANG_IN_D;
	if (ray_pov >= 360)
		ray_pov = ray_pov - 360;
	return (ray_pov);
	
}

void	casting_rays(t_table *table, t_ray *rays, t_position position)
{
	int	i;

	i = 1;
	while (i < N_RAY)
	{
		rays[i].index = i;
		rays[i].ray_pov = calcul_ray_pov(position, i);
		calcul_first_inter(table, rays[i], position);
		send_ray(table, rays[i], position);
		i++;
	}
}

start_exec(t_map *map)
{
	t_table 	table;
	t_position	position;
	t_ray		rays[1080];

	create_trigonometric_tables(6480, &table);
	init_player_position(map ,&position);
	casting_rays(&table, &rays[0], position);
	
}
