#include "../headers/cub3d.h"
#include "../headers/struct.h"
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))

void    init_player_position(t_map *map, t_position *pp)
{
	int v;

	v = map->pv;
	pp->x_cell = map->px;
	pp->y_cell = map->py;
	pp->virtual_px = pp->x_cell * CELL_SIZE + CELL_SIZE / 2;
	pp->virtual_py = pp->y_cell * CELL_SIZE + CELL_SIZE / 2;
	if (v == 'N')
	{
		pp->pov = N;
		pp->quadrant = 1;
	}
	else if (v == 'E')
	{
		pp->pov = E;
		pp->quadrant = 2;
	}
	else if (v == 'S')
	{
		pp->pov = S;
		pp->quadrant = 3;
	}
	else if (v == 'W')
	{
		pp->pov = W;
		pp->quadrant = 4;
	}
	pp->map = map;
}

void	ft_mlx_put_px(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int ft_mlx_get_px(t_texter *img, int x, int y)
{
	int color;

	color = img->addr[y*img->x + x];
	return (color);
}

void full_data(t_data *data, t_table *table, t_position *position, t_ray *ray)
{
	data->table = table;
	data->ray = ray;
	data->position = position;
}

void	ft_draw_ray(t_data *data, int i)
{
	int x0;
	int x1;
	int y0;
	int y1;
	int dx;
	int dy;
	int sx;
	int sy;
	int e2;
	int err;

	x0 = data->position->virtual_px;
	y0 = data->position->virtual_py;
	x1 = data->ray[i].x_save;
	y1 = data->ray[i].y_save;
	dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1; 
   	dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if(x0 < CELL_SIZE * data->map->map_w && y0 < CELL_SIZE * data->map->map_h)
			ft_mlx_put_px(data->mlx, x0, y0, 0x00b9ff);
		// else
		// {
		// 	printf("a = %d      b = %d\n", CELL_SIZE * data->map->map_w , CELL_SIZE * data->map->map_h);
		// 	printf("x1 = %d      y1 = %d\n", x1 , y1);
		// }
		e2 = 2 * err;
		if(e2 >= dx)
		{
			if(x0 == x1) break;
			err += dy; x0 += sx;
		}
		if(e2 <= dx)
		{
			if(y0 == y1) break;
			err += dx; y0 += sy;
		}

	}
}
void	draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int e2;
	int err;

	dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1; 
   	dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		ft_mlx_put_px(data->mlx, x0, y0, 0x873600);
		e2 = 2 * err;
		if(e2 >= dx)
		{
			if(x0 == x1) break;
			err += dy; x0 += sx;
		}
		if(e2 <= dx)
		{
			if(y0 == y1) break;
			err += dx; y0 += sy;
		}
	}
}

void	draw_3d(int i, t_data *data)
{
	int	t;
	int x0;
	int y0;
	int x1;
	int y1;

	t = 0;
	x0 = data->ray_w * i;
	y0 = (WIN_H - data->ray[i].ray_h) / 2;
	x1 = x0;
	y1 = y0 + data->ray[i].ray_h;
	while(t < data->ray_w)
	{
		draw_line(data, x0, y0, x1, y1);
		t++;
	}
}

void	get_texters(t_data *data)
{
	data->mlx->texters.N_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[0], &data->mlx->texters.N_img.x, &data->mlx->texters.N_img.y);
	data->mlx->texters.N_img.addr = (int *)mlx_get_data_addr(data->mlx->texters.N_img.img, &data->mlx->texters.N_img.bits_per_pixel, &data->mlx->texters.N_img.line_length, &data->mlx->texters.N_img.endian);
	data->mlx->texters.S_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[1], &data->mlx->texters.S_img.x, &data->mlx->texters.S_img.y);
	data->mlx->texters.S_img.addr = (int *)mlx_get_data_addr(data->mlx->texters.S_img.img, &data->mlx->texters.S_img.bits_per_pixel, &data->mlx->texters.S_img.line_length, &data->mlx->texters.S_img.endian);
	data->mlx->texters.W_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[2], &data->mlx->texters.W_img.x, &data->mlx->texters.W_img.y);
	data->mlx->texters.W_img.addr = (int *)mlx_get_data_addr(data->mlx->texters.W_img.img, &data->mlx->texters.W_img.bits_per_pixel, &data->mlx->texters.W_img.line_length, &data->mlx->texters.W_img.endian);
	data->mlx->texters.E_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[3], &data->mlx->texters.E_img.x, &data->mlx->texters.E_img.y);
	data->mlx->texters.E_img.addr = (int *)mlx_get_data_addr(data->mlx->texters.E_img.img, &data->mlx->texters.E_img.bits_per_pixel, &data->mlx->texters.E_img.line_length, &data->mlx->texters.E_img.endian);
	printf("img_x = %d     img_x = %d\n", data->mlx->texters.N_img.x, data->mlx->texters.N_img.y);
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
