/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:00:35 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/16 12:39:54 by Ma3ert           ###   ########.fr       */
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
	ang_in *= M_PI/180;
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
	if 
}

void	casting_rays(t_table *table, t_ray *rays, t_position position)
{
	int	ray;

	ray = 0;
	while (ray < N_RAY)
	{
		calcul_first_inter(table, rays[ray], position);
		send_ray(table, rays[ray], position);
		ray++;
	}
	
}

int	main ()
{
	t_table 	table;
	t_position	position;
	t_ray		rays[1080];

	create_trigonometric_tables(4, &table);
	init_player_position(&position);
	casting_rays(&table, &rays[0], position);
}
