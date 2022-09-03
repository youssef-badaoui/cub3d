#include "../../headers/cub3d.h"

void init_keystate (t_data *data)
{
	data->keystate.w = 0;
	data->keystate.a = 0;
	data->keystate.s = 0;
	data->keystate.d = 0;
	data->keystate.l = 0;
	data->keystate.r = 0;
	data->keystate.tir = 0;
}

void get_gun(t_data *data)
{
	data->gun[1] = "./gun/01.xpm";
	data->gun[2] = "./gun/02.xpm";
	data->gun[3] = "./gun/03.xpm";
	data->gun[4] = "./gun/04.xpm";
	data->gun[5] = "./gun/05.xpm";
	data->gun[6] = "./gun/06.xpm";
	data->gun[7] = "./gun/07.xpm";
	data->gun[8] = "./gun/08.xpm";
	data->gun[9] = "./gun/09.xpm";
	data->gun[10] = "./gun/10.xpm";
	data->gun[11] = "./gun/11.xpm";
	data->gun[12] = "./gun/12.xpm";
	data->gun[13] = "./gun/13.xpm";
	data->gun[14] = "./gun/14.xpm";
	data->gun[15] = "./gun/15.xpm";
	data->gun[16] = "./gun/16.xpm";
	data->gun[17] = "./gun/17.xpm";
	data->gun[18] = "./gun/18.xpm";
	data->gun[19] = "./gun/19.xpm";
	data->gun[20] = "./gun/20.xpm";
	data->gun[21] = "./gun/21.xpm";
	data->gun[22] = "./gun/22.xpm";
	data->gun[23] = "./gun/23.xpm";
	data->gun[24] = "./gun/24.xpm";
	data->gun[0] = "./gun/28.xpm";
}

void	calcul_cells(t_ray *ray)
{
	ray->xcell_v = ray->xbound / CELL_SIZE;
	ray->ycell_v = ray->yi / CELL_SIZE;
	ray->ycell_h = ray->ybound / CELL_SIZE;
	ray->xcell_h = ray->xi / CELL_SIZE;
	if (ray->ray_pov >= 180 && ray->ray_pov < 360)
		ray->xcell_v -= 1;
	if (ray->ray_pov <= 90 || ray->ray_pov > 270)
		ray->ycell_h -= 1;
}

void	check_skip(t_ray *ray, t_position position)
{
	if (ray->xcell_h > position.map->map_w || ray->ycell_h > position.map->map_h)
		ray->h_skip = 1;
	if (ray->xcell_v > position.map->map_w || ray->ycell_v > position.map->map_h)
		ray->v_skip = 1;
	if (ray->quadrant == 4)
	{
		if (ray->xcell_h > position.x_cell || ray->ycell_h > position.y_cell || ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
			
		if (ray->xcell_v > position.x_cell || ray->ycell_v > position.y_cell || ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	else if (ray->quadrant == 1)
	{
		if (ray->xcell_h < position.x_cell || ray->ycell_h > position.y_cell || ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;

		if (ray->xcell_v < position.x_cell || ray->ycell_v > position.y_cell || ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	else if (ray->quadrant == 2)
	{
		if (ray->xcell_h < position.x_cell || ray->ycell_h < position.y_cell || ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;

		if (ray->xcell_v < position.x_cell || ray->ycell_v < position.y_cell || ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	else if (ray->quadrant == 3)
	{
		if (ray->xcell_h > position.x_cell || ray->ycell_h < position.y_cell || ray->xcell_h < 0 || ray->ycell_h < 0)
			ray->h_skip = 1;
			
		if (ray->xcell_v > position.x_cell || ray->ycell_v < position.y_cell || ray->xcell_v < 0 || ray->ycell_v < 0)
			ray->v_skip = 1;
	}
	if (!(ray->h_skip) && ray->xcell_h > ft_strlen(position.map->map_tab[ray->ycell_h]))
		ray->h_skip = 1;
	if (!(ray->v_skip) && ray->xcell_v > ft_strlen(position.map->map_tab[ray->ycell_v]))
		ray->v_skip = 1;
}




