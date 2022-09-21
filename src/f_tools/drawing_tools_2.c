#include "../../headers/cub3d.h"

int get_x(t_data *data, int i)
{
    int x;

    if (data->ray[i].first == 'h')
		x = (int)data->ray[i].x_save % CELL_SIZE;
	else
		x = (int)data->ray[i].y_save % CELL_SIZE;
    return (x);
}
// int get_dx(t_data *data, int i)
// {
//     int x;

//     if (data->ray[i].first_d == 'h')
// 		x = (int)data->ray[i].xd_save % CELL_SIZE;
// 	else
// 		x = (int)data->ray[i].yd_save % CELL_SIZE;
//     return (x);
// }

t_texter *get_texter(t_data *data, int i)
{
    int x_cell;
    int y_cell;

    x_cell = data->ray[i].x_save / CELL_SIZE;
    y_cell = data->ray[i].y_save / CELL_SIZE;
    if (data->ray[i].ray_pov >= 180 && data->ray[i].first == 'v')
		x_cell -= 1;
	if ((data->ray[i].ray_pov <= 90 || data->ray[i].ray_pov > 270) && data->ray[i].first == 'h')
		y_cell -= 1;
    if(data->ray[i].door == DOOR_FOUND)
        return (&data->mlx->texters.C_door);
    if(data->ray[i].first == 'h')
    {
        if(data->ray[i].y_save >= data->position->virtual_py)
            if(data->map->map_tab[y_cell - 1][x_cell] == 'O')
                return (&data->mlx->texters.side);
            else
                return (&data->mlx->texters.S_img);
        else 
            if(data->map->map_tab[y_cell + 1][x_cell] == 'O')
                return (&data->mlx->texters.side);
            else
                return (&data->mlx->texters.N_img);
    }
    else   
    {
        if(data->ray[i].x_save >= data->position->virtual_px)
            if(data->map->map_tab[y_cell][x_cell - 1] == 'O')
                return (&data->mlx->texters.side);
            else
                return (&data->mlx->texters.E_img);
        else
            if(data->map->map_tab[y_cell][x_cell + 1] == 'O')
                return (&data->mlx->texters.side);
            else
                return (&data->mlx->texters.W_img);
    }
}