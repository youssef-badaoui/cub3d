#include "../headers/cub3d.h"

int tir_press(int keycode, int x, int y,t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		data->keystate.tir = 1;
	else if (keycode == 2)
		data->speed -= 13;
	return (0);
}

int tir_release(int keycode, int x, int y,t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		data->keystate.tir = 0;
	else if (keycode == 2)
		data->speed += 13;
	return (0);
}

int mouse_move(int  x, int y, t_data *data)
{
	(void) y;

	mlx_mouse_hide();
	data->position->pov = data->position->pov + (x - WIN_W / 2) / 20;
	if	(data->position->pov < 0)
		data->position->pov += 360;
	else if(data->position->pov > 360)
		data->position->pov -= 360;
	if(data->ray_h - (y - WIN_H / 2) / 5 < 100 && data->ray_h - (y - WIN_H / 2) / 5 > -200)
		data->ray_h -= (y - WIN_H / 2) / 5;
	mlx_mouse_move(data->mlx->win, WIN_W / 2, WIN_H / 2);
	return (0);
}

int move_handl(t_data *data)
{
	update_pov(data);
	update_position(data);
	drawing(data);
	button_press(data);
	return 0;
}

void open_close(int  keycode, t_data *data)
{
	int pov;
	int cell_x;
	int cell_y;

	if (keycode != 14)
		return ;
	cell_x = data->position->x_cell;
	cell_y = data->position->y_cell;
	pov = data->position->pov;
	if(pov <= 45 || pov >= 315)
		cell_y--;
	else if (pov > 45 && pov < 135)
		cell_x++;
	else if (pov > 135 && pov < 225)
		cell_y++;
	else if (pov > 225 && pov < 315)
		cell_x--;
	if (data->map->map_tab[cell_y][cell_x] == 'C')
		data->map->map_tab[cell_y][cell_x] = 'O';
	else if (data->map->map_tab[cell_y][cell_x] == 'O')
		data->map->map_tab[cell_y][cell_x] = 'C';
}

int keypress (int  keycode, t_data *data)
{
	open_close(keycode, data);
	if(keycode == 13)
		data->keystate.w = 1;
	else if(keycode == 0)
		data->keystate.a = 1;
	else if(keycode == 1)
		data->keystate.s = 1;
	else if(keycode == 2)
		data->keystate.d = 1;
	else if(keycode == 124)
		data->keystate.l = 1;
	else if(keycode == 123)
		data->keystate.r = 1;
	else if(keycode == 49)
		data->keystate.q = 1;
	else if(keycode == 53)
		data->keystate.esc = 1;
	else if(keycode == 35)
		data->keystate.o = 1;
	else if(keycode == 8)
		data->keystate.c = 1;
	return 0;
}

int keyrelease(int  keycode, t_data *data)
{
	if(keycode == 13)
		data->keystate.w = 0;
	else if(keycode == 0)
		data->keystate.a = 0;
	else if(keycode == 1)
		data->keystate.s = 0;
	else if(keycode == 2)
		data->keystate.d = 0;
	else if(keycode == 124)
		data->keystate.l = 0;
	else if(keycode == 123)
		data->keystate.r = 0;
	else if(keycode == 49)
		data->keystate.q = 0;
	else if(keycode == 35)
		data->keystate.o = 0;
	else if(keycode == 8)
		data->keystate.c = 0;
	return 0;
}


