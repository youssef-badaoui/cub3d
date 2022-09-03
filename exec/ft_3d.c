#include "../headers/cub3d.h"

void ft_cursur(t_data *data)
{
	draw_line(data, WIN_W/2 - 5, WIN_H/2, WIN_W/2+5,  WIN_H/2);
	draw_line(data, WIN_W/2, WIN_H/2-5, WIN_W/2, WIN_H/2+5);
}

void	ft_ray_handl(t_data *data, int i)
{
	int j;
	int	x;
	int wall_h;
	int x_img;
	double img_pls_y;
	if(data->ray[i].first == 'h')
		x = (int)data->ray[i].x_save % CELL_SIZE;
	else
		x = (int)data->ray[i].y_save % CELL_SIZE;
	wall_h = data->ray[i].ray_h;
	x_img = x * (data->mlx->texters.N_img.x / CELL_SIZE);
	img_pls_y = (double)data->mlx->texters.N_img.y / (double)wall_h;
	j = 0;
	while(j < wall_h)
	{
		ft_mlx_put_px(data->mlx, i, j + (WIN_H/2 - wall_h/2), ft_mlx_get_px(&data->mlx->texters.N_img, x_img, j * img_pls_y));
		j++;
	}
}

void	ft_3d(t_data *data)
{
	int	i;

	i = 0;
	data->ray_w = WIN_W / N_RAY;
	if(!data->ray_w)
		data->ray_w = 1;
	while(i < N_RAY)
	{
		data->ray[i].save_distance = data->ray[i].save_distance *  data->table->cos_table[abs(N_RAY/2 - i)];
		if(data->ray[i].save_distance/CELL_SIZE)
			data->ray[i].ray_h = WIN_H / (data->ray[i].save_distance/CELL_SIZE);
		ft_ray_handl(data, i);
		ft_cursur(data);
		i++;
	}
}