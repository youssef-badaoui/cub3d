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

int get_dx(t_data *data, int i)
{
    int x;

    if (data->ray[i].first_d == 'h')
		x = (int)data->ray[i].xd_save % CELL_SIZE;
	else
		x = (int)data->ray[i].yd_save % CELL_SIZE;
    return (x);
}

t_texter *get_texter(t_data *data, int i)
{
    int x_cell;
    int y_cell;

    x_cell = data->position->x_cell;
    y_cell = data->position->y_cell;
    if(data->map->map_tab[y_cell][x_cell] == 'O')
        return (&data->mlx->texters.fog);
    if(data->ray[i].first == 'h')
    {
        if(data->ray[i].y_save >= data->position->virtual_py)
            return (&data->mlx->texters.S_img);
        else
            return (&data->mlx->texters.N_img);
    }
    else   
    {
        if(data->ray[i].x_save >= data->position->virtual_px)
            return (&data->mlx->texters.E_img);
        else
            return (&data->mlx->texters.W_img);
    }
}