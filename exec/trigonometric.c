/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:00:35 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/16 15:36:20 by ybadaoui         ###   ########.fr       */
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
	if ()
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

	i = 0;
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
