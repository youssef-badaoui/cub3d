/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:01 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/10 16:28:53 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	ft_color_win(t_data *data, t_mlx *mlx, int ray_h)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			if (y > WIN_H / 2 + ray_h)
			{
				ft_mlx_put_px(mlx, x, y, data->map->int_f);
				y++;
			}
			else
			{
				ft_mlx_put_px(mlx, x, y, data->map->int_c - (double)y / (2.5));
				y++;
			}
		}
		x++;
	}
}

int	ft_mlx_get_px(t_texter *img, int x, int y)
{
	int	color;

	if (x >= img->x - 1 || y >= img->y - 1 || x < 0 || y < 0)
		return (0);
	color = img->addr[y * img->x + x];
	return (color);
}

void	draw_it(t_data *data)
{
	while (1)
	{
		ft_mlx_put_px(data->mlx, data->line_param.x0,
			data->line_param.y0, 0x9300ff);
		data->e2 = 2 * data->err;
		if (data->e2 >= data->dx)
		{
			if (data->line_param.x0 == data->line_param.x1)
				break ;
			data->err += data->dy;
			data->line_param.x0 += data->sx;
		}
		if (data->e2 <= data->dx)
		{
			if (data->line_param.y0 == data->line_param.y1)
				break ;
			data->err += data->dx;
			data->line_param.y0 += data->sy;
		}
	}
}

void	draw_line(t_data *data)
{
	data->dx = abs(data->line_param.x1 - data->line_param.x0);
	if (data->line_param.x0 < data->line_param.x1)
		data->sx = 1;
	else
		data->sx = -1;
	if (data->line_param.y0 < data->line_param.y1)
		data->sy = 1;
	else
		data->sy = -1;
	data->dy = -abs(data->line_param.y1 - data->line_param.y0);
	data->err = data->dx + data->dy;
	draw_it(data);
}

void	ft_mlx_put_px(t_mlx *mlx, int x, int y, unsigned long color)
{
	char	*dst;

	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
