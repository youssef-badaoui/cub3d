/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:13:46 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/12 22:29:00 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_cursur(t_data *data)
{
	data->line_param.x0 = WIN_W / 2 - 5;
	data->line_param.y0 = WIN_H / 2;
	data->line_param.x1 = WIN_W / 2 + 5;
	data->line_param.y1 = WIN_H / 2;
	draw_line(data);
	data->line_param.x0 = WIN_W / 2;
	data->line_param.y0 = WIN_H / 2 - 5;
	data->line_param.x1 = WIN_W / 2;
	data->line_param.y1 = WIN_H / 2 + 5;
	draw_line(data);
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
	if (!x_img)
		x_img = 1;
	wall_h = data->ray[ray_index].ray_h;
	if (texter == &data->mlx->texters.fog)
		wall_h = WIN_H;
	img_pls_y = (double)texter->y / (double)wall_h;
	j = 0;
	if (data->ray_h + j + (WIN_H / 2 - wall_h / 2) < 0)
		j = -1 * data->ray_h - (WIN_H / 2 - wall_h / 2);
	while (j < wall_h)
	{
		if (data->ray_h + j + (WIN_H / 2 - wall_h / 2) > WIN_H)
			break ;
		ft_mlx_put_px(data->mlx, ray_index, data->ray_h + j + (WIN_H / 2 \
			- wall_h / 2), ft_mlx_get_px(texter, (int)x_img, j * img_pls_y));
		j++;
	}
}

void	ft_3d(t_data *data)
{
	int		i;
	double	dis;
	int		x_cell;
	int		y_cell;

	x_cell = data->position->x_cell;
	y_cell = data->position->y_cell;
	i = 0;
	while (i < N_RAY)
	{
		dis = data->ray[i].save_distance
			* data->table->cos_table[abs(N_RAY / 2 - i)];
		if (dis / CELL_SIZE)
			data->ray[i].ray_h = WIN_H / (dis / CELL_SIZE);
		ft_ray_handl(data, i);
		ft_cursur(data);
		i++;
	}
}
