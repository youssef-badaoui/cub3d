#include "../headers/cub3d.h"

void ft_cursur(t_data *data)
{
	draw_line(data, WIN_W/2 - 5, WIN_H/2, WIN_W/2+5,  WIN_H/2);
	draw_line(data, WIN_W/2, WIN_H/2-5, WIN_W/2, WIN_H/2+5);
}

void	ft_ray_handl(t_data *data, int ray_index)
{
	int j;
	int wall_h;
	int x_img;
	double img_pls_y;
	t_texter *texter;

	texter = get_texter(data, ray_index);
	x_img = get_x(data, ray_index) * (texter->x / CELL_SIZE);
	wall_h = data->ray[ray_index].ray_h;
	img_pls_y = (double)texter->y / (double)wall_h;
	j = 0;
	while(j < wall_h)
	{
		ft_mlx_put_px(data->mlx, ray_index,data->ray_h + j + (WIN_H/2 - wall_h/2), ft_mlx_get_px(texter, x_img, j * img_pls_y));
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