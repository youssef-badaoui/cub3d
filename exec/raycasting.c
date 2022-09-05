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

void	calcul_first_vertical(t_table *table, t_ray *ray, t_position position)
{
	double	diff;
	double	side;

	diff = position.virtual_py;
	side = 0.0;
	if (ray->ray_pov < 180 && ray->ray_pov >= 0)
	{
		ray->xbound = CELL_SIZE * (position.x_cell + 1);
		ray->x_step = CELL_SIZE;
		side = ray->xbound - position.virtual_px;
	}
	else
	{
		ray->xbound = CELL_SIZE * position.x_cell;
		ray->x_step = CELL_SIZE * (-1.0);
		side = position.virtual_px - ray->xbound;
	}
	if (ray->quadrant == 1 || ray->quadrant == 3)
		ray->yi = calcul_adjacent(table->tan_table[ray->index], side);
	else
		ray->yi = calcul_opposite(table->tan_table[ray->index], side);
	if (ray->quadrant == 4 || ray->quadrant == 1)
		ray->yi = diff - ray->yi;
	else
		ray->yi = diff + ray->yi;
}

void	calcul_first_horizontal(t_table *table, t_ray *ray, t_position position)
{
	double	diff;
	double	side;

	diff = position.virtual_px;
	side = 0.0;
	if (ray->ray_pov > 270 || ray->ray_pov <= 90)
	{
		ray->y_step = CELL_SIZE * (-1.0);
		ray->ybound = position.y_cell * CELL_SIZE;
		side = position.virtual_py - ray->ybound;
	}
	else
	{
		ray->y_step = CELL_SIZE;
		ray->ybound = (position.y_cell + 1) * CELL_SIZE;
		side = ray->ybound - position.virtual_py;
	}
	if (ray->quadrant == 2 || ray->quadrant == 4)
		ray->xi = calcul_adjacent(table->tan_table[ray->index], side);
	else
		ray->xi = calcul_opposite(table->tan_table[ray->index], side);
	if (ray->quadrant == 3 || ray->quadrant == 4)
		ray->xi = diff - ray->xi;
	else
		ray->xi = diff + ray->xi;
}

void	casting_rays(t_table *table, t_ray *rays, t_position position)
{
	int	i;

	i = 0;
	while (i < N_RAY)
	{
		rays[i].ray_pov = calcul_ray_pov(position, i);
		rays[i].index = calcul_ray_angle(&rays[i], rays[i].ray_pov);
		calcul_first_vertical(table, &rays[i], position);
		calcul_first_horizontal(table, &rays[i], position);
		rays[i].h_door = 0;
		rays[i].v_door = 0;
		rays[i].h_hit = 0;
		rays[i].v_hit = 0;
		rays[i].h_skip = 0;
		rays[i].v_skip = 0;
		rays[i].first = 0;
		send_ray(table, &rays[i], position);
		i++;
	}
}