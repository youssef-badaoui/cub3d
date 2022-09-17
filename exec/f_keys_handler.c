#include "../headers/cub3d.h"

void	update_pov(t_data *data)
{
	if (data->keystate.l)
		data->position->pov = data->position->pov + 3;
	else if (data->keystate.r)
		data->position->pov = data->position->pov - 3;
	if (data->position->pov < 0)
		data->position->pov += 360;
	else if (data->position->pov > 360)
		data->position->pov -= 360;
}

void	walking_sound(void)
{
	char		*arg[3];
	int			pid;
	static int	t;

	if (!t)
	{
		t = 18;
		pid = fork();
		if (pid == 0)
		{
			arg[1] = "./sounds/walk.mp3";
			arg[0] = "/usr/bin/afplay";
			arg[2] = NULL;
			execve(arg[0], arg, NULL);
		}
	}
	else
		t--;
}

void	update_position(t_data *data)
{
	double	pov;
	int		pov_index;

	if (!set_pov(data, &pov))
		return ;
	pov_index = pov / ANG_IN_D;
	walking_sound();
	if (wall_detect(data, pov_index))
		return ;
	data->position->virtual_px += data->table->sin_table[pov_index]
		* CELL_SIZE / 13;
	data->position->virtual_py -= data->table->cos_table[pov_index]
		* CELL_SIZE / 13;
	data->position->x_cell = data->position->virtual_px / CELL_SIZE;
	data->position->y_cell = data->position->virtual_py / CELL_SIZE;
}

int	button_press(t_data *data)
{
	double static	i;
	void			*img;
	int				x;
	int				y;

	if (data->keystate.tir == 1)
	{	
		img = mlx_xpm_file_to_image(data->mlx->mlx, data->gun[(int)i], &x, &y);
		mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
			img, WIN_W - x, WIN_H - y);
		i += 0.5;
	}
	if (i >= 25)
		i = 0;
	return (0);
}

int	set_pov(t_data *data, double *pov)
{
	*pov = data->position->pov;
	if (data->keystate.d)
		*pov += 90.0;
	else if (data->keystate.a)
		*pov += 270.0;
	else if (data->keystate.s)
		*pov += 180.0;
	else if (!data->keystate.w)
		return (0);
	if (*pov >= 360)
		*pov -= 360;
	if (*pov < 0)
		*pov += 360;
	return (1);
}

int	wall_detect(t_data *data, int index)
{
	int	next_x;
	int	next_y;
	int	x;
	int	y;

	x = data->position->x_cell;
	y = data->position->y_cell;
	next_x = (data->position->virtual_px + data->table->sin_table[index]
			* CELL_SIZE / 13) / CELL_SIZE;
	next_y = (data->position->virtual_py - data->table->cos_table[index]
			* CELL_SIZE / 13) / CELL_SIZE;
	if (next_y >= data->map->map_h || next_x >= data->map->map_w)
		return (1);
	if (!ft_strchr(data->map->map_tab[next_y][x], "0NESWO") && !ft_strchr(data->map->map_tab[y][next_x], "0NESWO"))
		return (1);
	if (!ft_strchr(data->map->map_tab[next_y][next_x], "0NESWO"))
		return (1);
	return (0);
}

