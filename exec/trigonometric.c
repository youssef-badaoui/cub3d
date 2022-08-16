/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:00:35 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/16 15:03:39 by Ma3ert           ###   ########.fr       */
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
	ang_in = 360.0 / (double)narc;
	ang_in *= M_PI/180.0;
	tan_res = malloc(sizeof(double) * narc);
	while (i < narc)
	{
		angle = i * ang_in;
		tan_res[i] = tan(angle);
		printf("tan = %lf\n", tan_res[i]);
		i++;
	}
	table->tan_table = tan_res;
}

void	send_ray(t_table *table, t_ray ray, t_position position)
{
	
}

void	calcul_first_inter(t_table *table, t_ray ray, t_position position)
{
	if ()
}

double	calcul_ray_pov(t_position position, int ray)
{
	double	ray_pov;

	if (ray < 540)
	{
		ray_pov = position.pov - HALF_FOV;
		if (ray_pov < 0)
			ray_pov += 360;
		ray_pov += ray * (60 / 1080);
	}
	else
	{
		ray_pov = position.pov + HALF_FOV;
		if (ray_pov > 360)
			ray_pov -= 360;
	}
}

void	casting_rays(t_table *table, t_ray *rays, t_position position)
{
	int	i;
	double	ang_in;

	ang_in = 360.0 / 6480.0;
	ang_in *= M_PI / 180.0;
	i = 0;
	while (i < N_RAY)
	{
		rays[i].angle = i * ang_in;
		calcul_ray_pov(position, i);
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
