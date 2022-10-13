/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:13:17 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/13 14:33:02 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	put_gun(t_data *data)
{
	static double	i;
	int				x;
	int				y;
	void			*img;

	img = mlx_xpm_file_to_image(data->mlx->mlx, data->gun[(int)i], &x, &y);
	if (!data->keystate.w)
		img = mlx_xpm_file_to_image(data->mlx->mlx, data->gun[0], &x, &y);
	if (data->keystate.tir == 0)
		mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
			img, WIN_W - x, WIN_H - y + 60);
		i += 0.1;
	if (i == 1)
		i = 2;
	else if (i == 3)
		i = 4;
	else
		i = 0;
}

void	color_sqr(t_data *data, int x, int y, unsigned int color)
{
	int	xc;
	int	yc;

	xc = 0;
	while (xc <= data->cell_size)
	{
		yc = 0;
		while (yc <= data->cell_size)
		{
			if (yc == 0 || xc == 0)
				ft_mlx_put_px(data->mlx, xc + (data->cell_size * x),
					yc + (data->cell_size * y), 0x0);
			else
				ft_mlx_put_px(data->mlx, xc + (data->cell_size * x),
					yc + (data->cell_size * y), color);
			yc++;
		}
		xc++;
	}
}

void	put_rays(t_data *data, double diff)
{
	int		i;
	double	px;
	double	py;
	int		x;
	int		y;

	i = 0;
	px = data->position->virtual_px / diff;
	py = data->position->virtual_py / diff;
	while (i < N_RAY)
	{
		x = data->ray[i].x_save;
		y = data->ray[i].y_save;
		data->line_param.x0 = px;
		data->line_param.y0 = py;
		data->line_param.x1 = x / diff;
		data->line_param.y1 = y / diff;
		draw_line(data);
		i++;
	}
}

void	put_map(t_data *data)
{
	int	x;
	int	y;

	if (data->keystate.q)
		data->cell_size = WIN_W / data->map->map_w;
	else
		data->cell_size = 10;
	y = 0;
	while (data->map->map_tab[y])
	{
		x = 0;
		while (data->map->map_tab[y][x])
		{
			if (ft_strchr(data->map->map_tab[y][x], "C1"))
				color_sqr(data, x, y, 0x0);
			else if (!ft_is_whitespace(data->map->map_tab[y][x]))
				color_sqr(data, x, y, 0xd2b4de);
			x++;
		}
		y++;
	}
	put_rays(data, (double)CELL_SIZE / data->cell_size);
	mlx_put_image_to_window(data->mlx->mlx,
		data->mlx->win, data->mlx->img, 0, 0);
}

void	drawing(t_data *data)
{
	if (data->keystate.esc)
	{
		ft_print("game finished hope you enjoy it ;)\n");
		exit(0);
	}
	casting_rays(data->table, data->ray, *data->position);
	ft_color_win(data, data->mlx, data->ray_h);
	ft_3d(data);
	put_map(data);
	put_gun(data);
}
