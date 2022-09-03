#include "../../headers/cub3d.h"

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
