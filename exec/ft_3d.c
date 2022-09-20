#include "../headers/cub3d.h"

void	ft_cursur(t_data *data)
{
	draw_line(data, WIN_W / 2 - 5, WIN_H / 2, WIN_W / 2 + 5,  WIN_H / 2);
	draw_line(data, WIN_W / 2, WIN_H / 2 - 5, WIN_W / 2, WIN_H / 2 + 5);
}

void	ft_ray_handl(t_data *data, int ray_index)
{
	int			j;
	int			wall_h;
	double		x_img;
	double		img_pls_y;
	t_texter	*texter;

	texter = get_texter(data, ray_index);
	x_img = get_x(data, ray_index) * ((double)texter->x / CELL_SIZE);
	if(!x_img)
		x_img = 1;
	wall_h = data->ray[ray_index].ray_h;
	if(texter == &data->mlx->texters.fog)
		wall_h = WIN_H;
	img_pls_y = (double)texter->y / (double)wall_h;
	j = 0;
	while (j < wall_h)
	{
		ft_mlx_put_px(data->mlx, ray_index,data->ray_h + j + (WIN_H/2
			- wall_h/2), ft_mlx_get_px(texter, (int)x_img, j * img_pls_y));
		j++;
	}
}

void	*get_door_texter(t_data *data, int index)
{
	if (data->ray[index].h_dd == data->ray[index].door_dis)
	{
		if (data->ray[index].hdoor_state == CLOSE)
			return (&data->mlx->texters.C_door);
		else
			return (&data->mlx->texters.O_door);
	}
	else
	{
		if (data->ray[index].vdoor_state == CLOSE)
			return (&data->mlx->texters.C_door);
		else
			return (&data->mlx->texters.O_door);
	}
	return (NULL);
}

void	ft_door_handl(t_data *data, int ray_index)
{
	int			j;
	int			wall_h;
	double			x_img;
	double		img_pls_y;
	t_texter	*texter;
	double dis;

	dis = data->ray[ray_index].door_dis * data->table->cos_table[abs(N_RAY / 2 - ray_index)];
	texter = get_door_texter(data, ray_index);
	wall_h = 0;
	x_img = get_dx(data, ray_index) * ((double)texter->x / CELL_SIZE);
	if(dis / CELL_SIZE)
		wall_h = WIN_H / (dis / CELL_SIZE);
	img_pls_y = (double)texter->y / wall_h;
	j = 0;
	while (j < wall_h)
	{
		ft_mlx_put_px(data->mlx, ray_index,data->ray_h + j + (WIN_H / 2 - wall_h / 2), ft_mlx_get_px(texter, x_img, j * img_pls_y));
		j++;
	}
}

void	ft_3d(t_data *data)
{
	int	i;
	double dis;
	int x_cell;
    int y_cell;

    x_cell = data->position->x_cell;
    y_cell = data->position->y_cell;

	i = 0;
	dis = data->ray[i].save_distance;
	while (i < N_RAY)
	{
		dis = data->ray[i].save_distance * data->table->cos_table[abs(N_RAY / 2 - i)];
		if (dis / CELL_SIZE)
			data->ray[i].ray_h = WIN_H / (dis / CELL_SIZE);
		ft_ray_handl(data, i);
		ft_cursur(data);
		i++;
	}
	i = 0;
    if(data->map->map_tab[y_cell][x_cell] == 'O')
        return ;
	// mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0 ,0);
	while (i < N_RAY)
	{
		if ((data->ray[i].h_door == DOOR_FOUND || data->ray[i].v_door == DOOR_FOUND) && data->ray[i].door_dis <= data->ray[i].save_distance)
			ft_door_handl(data, i);
		i++;
	}
}