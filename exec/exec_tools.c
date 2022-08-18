#include "../headers/cub3d.h"
#include "../headers/struct.h"

void    init_player_position(t_map *map, t_position *pp)
{
	int v;

	v = map->pv;
	pp->x_cell = map->px;
	pp->y_cell = map->py;
	pp->virtual_px = pp->x_cell * CELL_SIZE + CELL_SIZE / 2;
	pp->virtual_py = pp->y_cell * CELL_SIZE + CELL_SIZE / 2;
	if (v == 'N')
		pp->pov = N;
	else if (v == 'E')
		pp->pov = E;
	else if (v == 'S')
		pp->pov = S;
	else if (v == 'W')
		pp->pov = W;
	pp->map = map;
}

void	ft_mlx_put_px(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	dst = color;
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
	x1 = data->ray[i].xi;
	y1 = data->ray[i].yi;
	dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1; 
   	dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		ft_mlx_put_px(data->mlx, x0, y0, 0xD3FAD6);
		printf("x0 = %d     y0 = %d\n", x0, y0);
		printf("x1 = %d     y1 = %d\n", x1, y1);
		sleep(1);
		e2 = 2 * err;
		if(e2 >= dx)
		{
			if(x0 == x1) break;
			err += dy; y0 += sy;
		}
		if(e2 <= dx)
		{
			if(y0 == y1) break;
			err += dx; y0 += sy;
		}
		printf("hoooolaaaaaa2!\n");
	}
}