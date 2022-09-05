#include "../headers/cub3d.h"

void	calcul_next_h_inter(t_table *table, t_ray *ray, t_position position)
{
	double	yside;
	
	yside = 0;
	if (ray->ray_pov > 270 || ray->ray_pov <= 90)
		yside = position.virtual_py - ray->ybound;
	else
		yside = ray->ybound - position.virtual_py;
	if (ray->quadrant == 1 || ray->quadrant == 3)
		ray->xi = calcul_opposite(table->tan_table[ray->index], yside);
	else
		ray->xi = calcul_adjacent(table->tan_table[ray->index], yside);
	if (ray->quadrant == 3 || ray->quadrant == 4)
		ray->xi = position.virtual_px - ray->xi;
	else
		ray->xi = position.virtual_px + ray->xi;
}

void	calcul_next_v_inter(t_table *table, t_ray *ray, t_position position)
{
	double	xside;
	
	xside = 0;
	if (ray->ray_pov <= 180 && ray->ray_pov > 0)
		xside = ray->xbound - position.virtual_px;
	else
		xside = position.virtual_px - ray->xbound;
	if (ray->quadrant == 1 || ray->quadrant == 3)
		ray->yi = calcul_adjacent(table->tan_table[ray->index], xside);
	else
		ray->yi = calcul_opposite(table->tan_table[ray->index], xside);
	if (ray->quadrant == 4 || ray->quadrant == 1)
		ray->yi = position.virtual_py - ray->yi;
	else
		ray->yi = position.virtual_py + ray->yi;
}

void	calcul_distance(t_table *table, t_ray *ray, t_position position)
{
	triangle_sides(ray, position, table);
	if ((ray->h_distance < ray->v_distance || ray->v_skip) && !(ray->h_skip))
	{
		ray->x_save = ray->xi;
		ray->y_save = ray->ybound;
		ray->save_distance = ray->h_distance;
		ray->first = 'h';
	}
	else
	{
		ray->x_save = ray->xbound;
		ray->y_save = ray->yi;
		ray->save_distance = ray->v_distance;
		ray->first = 'v';
	}
}

void	calcul_door_vdistance(t_ray *ray, t_position position, t_table table)
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
		ray->v_distance = opposite / table->sin_table[ray->index];
	else
		ray->v_distance = adjacent / table->cos_table[ray->index];
}

void	calcul_door_hdistance(t_ray *ray, t_position position, t_table table)
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
		ray->h_distance = adjacent / table->cos_table[ray->index];
	else
		ray->h_distance = opposite / table->sin_table[ray->index];
}

void	check_door(t_ray *ray, t_position position, t_table table)
{
	if (!(ray->h_skip) && !(ray->h_door) && (position.map->map_tab[ray->ycell_h][ray->xcell_h] == 'C' ||
		position.map->map_tab[ray->ycell_h][ray->xcell_h] == 'O'))
	{
		ray->h_door = DOOR_FOUND;
		calcul_door_hdistance(ray, position, table);
		if (position.map->map_tab[ray->ycell_h][ray->xcell_h] == 'C')
			ray->hdoor_state = CLOSE;
		else
			ray->hdoor_state = OPEN;
	}
	if ( !(ray->v_door) && !(ray->v_skip) && (position.map->map_tab[ray->ycell_v][ray->xcell_v] == 'C' ||
		position.map->map_tab[ray->ycell_v][ray->xcell_v] == 'O'))
	{
		ray->v_door = DOOR_FOUND;
		calcul_door_vdistance(ray, position, table);
		if (position.map->map_tab[ray->ycell_v][ray->xcell_v] == 'C')
			ray->vdoor_state = CLOSE;
		else
			ray->vdoor_state = OPEN;
	}
}

int	check_cell_type(t_ray *ray, t_position position, t_table table)
{
	calcul_cells(ray);
	check_skip(ray, position);
	check_door(ray, position, table);
	if (!(ray->h_skip) && position.map->map_tab[ray->ycell_h][ray->xcell_h] == '1' || ray->hdoor_state == CLOSE)
		ray->h_hit = INTERSECTION_FOUND;
	if (!(ray->v_skip) && position.map->map_tab[ray->ycell_v][ray->xcell_v] == '1' || ray->vdoor_state == CLOSE)
		ray->v_hit = INTERSECTION_FOUND;
	if (ray->v_hit && ray->h_hit)
		return (INTERSECTION_FOUND);
	else if (ray->h_hit && ray->v_skip)
		return (INTERSECTION_FOUND);
	else if (ray->v_hit && ray->h_skip)
		return (INTERSECTION_FOUND);
	return (0);
}

void	send_ray(t_table *table, t_ray *ray, t_position position)
{
	int	inter;

	inter = 0;
	while (1)
	{
		inter = check_cell_type(ray, position, table);
		if (inter == INTERSECTION_FOUND)
			return (calcul_distance(table, ray, position));
		if (!(ray->v_hit) && !(ray->v_skip))
		{
			ray->xbound += ray->x_step;
			calcul_next_v_inter(table, ray, position);
		}
		if (!(ray->h_hit) && !(ray->h_skip))
		{
			ray->ybound += ray->y_step;
			calcul_next_h_inter(table, ray, position);
		}
	}
}