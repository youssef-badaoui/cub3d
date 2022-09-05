#include "../headers/cub3d.h"

void	put_gun(t_data *data)
{
	static double i;
	int x;
	int y;
	void *img;

	img = mlx_xpm_file_to_image(data->mlx->mlx, data->gun[(int)i],&x, &y);
	if (!data->keystate.w)
		img = mlx_xpm_file_to_image(data->mlx->mlx, data->gun[0],&x, &y);
	if (data->keystate.tir == 0)
		mlx_put_image_to_window(data->mlx->mlx,data->mlx->win, img, WIN_W - x, WIN_H-y);
		i+= 0.1;
	if (i > 2 && i < 8)
		i = 8;
	if (i > 11)
		i = 0;
}

void	color_sqr(t_data *data, int cell_size, int x, int y, unsigned int color)
{
	int	xc;
	int	yc;

	xc = 0;
	while (xc <= cell_size)
	{
		yc = 0;
		while( yc <= cell_size)
		{
			if(yc == 0 || xc == 0)
				ft_mlx_put_px(data->mlx, xc + (cell_size * x), yc + (cell_size * y), 0x0);
			else
				ft_mlx_put_px(data->mlx, xc + (cell_size * x), yc + (cell_size * y), color);
			yc++;
		}
		xc++;
	}
}

void put_rays(t_data *data, double diff)
{
	int i;
	double px;
	double py;

	i = 0;
	px = data->position->virtual_px / diff;
	py = data->position->virtual_py / diff;
	while(i < N_RAY)
	{
		draw_line(data, px, py, data->ray[i].x_save / diff, data->ray[i].y_save / diff);
		i++;
	}
}

void put_map(t_data *data)
{
	int cell_size;
	int x;
	int y;

	if(data->keystate.q)
		cell_size = 30;
	else
		cell_size = 10;
	y = 0;
	while(y < data->map->map_h)
	{
		x = 0;
		while(x < data->map->map_w)
		{
			if(data->map->map_tab[y][x] == '1')
				color_sqr(data, cell_size, x, y, 0x0);
			else if (!ft_is_whitespace(data->map->map_tab[y][x]))
				color_sqr(data, cell_size, x, y, 0xd2b4de);
			x++;
		}
		y++;
	}
	put_rays(data, CELL_SIZE / cell_size);
	mlx_put_image_to_window(data->mlx->mlx,data->mlx->win, data->mlx->img, 0,0);
}

void drawing(t_data *data)
{
	if(data->keystate.esc)
	{
		ft_print("game finished hope you enjoy it ;)\n");
		exit(0);
	}
	casting_rays(data->table, data->ray, *data->position);
	ft_color_win(data->mlx,data->ray_h);
	ft_3d(data);
	put_map(data);
	put_gun(data);

}