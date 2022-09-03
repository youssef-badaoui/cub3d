#include "../../headers/cub3d.h"

void	ft_color_image(t_mlx *mlx,  int color, int i , int j)
{
	int x;
	int y;

	x = 0;
	while(x < CELL_SIZE)
	{
		y = 0;
		while(y < CELL_SIZE)
		{
			if(x == 0 || y == 0)
				ft_mlx_put_px(mlx, x + j * CELL_SIZE, i * CELL_SIZE + y++ , 0x0);
			else
				ft_mlx_put_px(mlx, x + j * CELL_SIZE, i * CELL_SIZE + y++ , color);
		}
			
		x++;
	}
}

void	ft_color_win(t_mlx *mlx,  int color)
{
	int x;
	int y;

	color =0;
	x = 0;
	while(x < WIN_W)
	{
		y = 0;
		while(y < WIN_H)
		{
			if(y > WIN_H/2)
			{
				ft_mlx_put_px(mlx, x, y, 0x22122a);
				y++;
			}
			else
			{
				ft_mlx_put_px(mlx, x, y, 0xa569bd-y/2);
				y++;
			}
				
		}
		x++;
	}
}

int ft_mlx_get_px(t_texter *img, int x, int y)
{
	int color;

	if(x >= img->x-1 || y >= img->y-1 || x < 0 || y < 0)
		return 0;
	color = img->addr[y * img->x + x];
	return (color);
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
		ft_mlx_put_px(data->mlx, x0, y0, 0xc62300);
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

void	ft_mlx_put_px(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	if(x >= WIN_W || y >= WIN_H || x < 0||y < 0)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



