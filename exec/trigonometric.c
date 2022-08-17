/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:45:34 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/17 15:52:55 by Ma3ert           ###   ########.fr       */
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
	ycell_h = ray->xi / CELL_SIZE;
	if (position.map->map_tab[xcell_h][ycell_h] == '1')
		ray->h_hit = INTERSECTION_FOUND;
	if (position.map->map_tab[xcell_v][ycell_v] == '1')
		ray->v_hit = INTERSECTION_FOUND;
	if (ray->v_hit || ray->v_hit)
		return (1);
	return (0);
}

void	calcul_next_inter(t_table *table, t_ray *ray, t_position position)
{
	ray->xbound += ray->x_step;
	ray->ybound += ray->y_step;
}

void	send_ray(t_table *table, t_ray *ray, t_position position)
{
	int	inter;

	inter = 0;
	while (inter != INTERSECTION_FOUND)
	{
		if (check_cell_type(ray, position))
			calcul_distance();
		calcul_next_inter(table, ray, position);
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

start_exec(t_map *map)
{
	t_table 	table;
	t_position	position;
	t_ray		rays[1080];

	create_trigonometric_tables(6480, &table);
	init_player_position(map ,&position);
	casting_rays(&table, &rays[0], position);
	mini_map(map, rays);
}

void mini_map(t_map *map, t_ray *rays)
{
	t_mlx mlx;
	t_data data;
	
	full_data(&data);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 400, 400, "call of duty");
	mlx.img = mlx_new_image(mlx.mlx, 400, 400);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	
}
void	ft_draw_ray(t_data data)
{
	
}
