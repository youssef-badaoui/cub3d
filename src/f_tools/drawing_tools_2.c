/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:12 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/05 12:21:13 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	get_x(t_data *data, int i)
{
	int	x;

	if (data->ray[i].first == 'h')
		x = (int)data->ray[i].x_save % CELL_SIZE;
	else
		x = (int)data->ray[i].y_save % CELL_SIZE;
	return (x);
}

int	keypress(int keycode, t_data *data)
{
	open_close(keycode, data);
	if (keycode == 13)
		data->keystate.w = 1;
	else if (keycode == 0)
		data->keystate.a = 1;
	else if (keycode == 1)
		data->keystate.s = 1;
	else if (keycode == 2)
		data->keystate.d = 1;
	else if (keycode == 124)
		data->keystate.l = 1;
	else if (keycode == 123)
		data->keystate.r = 1;
	else if (keycode == 49)
		data->keystate.q = 1;
	else if (keycode == 53)
		data->keystate.esc = 1;
	else if (keycode == 35)
		data->keystate.o = 1;
	else if (keycode == 8)
		data->keystate.c = 1;
	return (0);
}

int	keyrelease(int keycode, t_data *data)
{
	if (keycode == 13)
		data->keystate.w = 0;
	else if (keycode == 0)
		data->keystate.a = 0;
	else if (keycode == 1)
		data->keystate.s = 0;
	else if (keycode == 2)
		data->keystate.d = 0;
	else if (keycode == 124)
		data->keystate.l = 0;
	else if (keycode == 123)
		data->keystate.r = 0;
	else if (keycode == 49)
		data->keystate.q = 0;
	else if (keycode == 35)
		data->keystate.o = 0;
	else if (keycode == 8)
		data->keystate.c = 0;
	return (0);
}
