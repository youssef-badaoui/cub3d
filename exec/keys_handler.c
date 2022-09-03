#include "../headers/cub3d.h"

int tir_press(int keycode, int x, int y,t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		data->keystate.tir = 1;
	return (0);
}

int tir_release(int keycode, int x, int y,t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		data->keystate.tir = 0;
	return (0);
}

int mouse_move(int  x, int y, t_data *data)
{
	static int mouse_x;
	
	if(x > mouse_x && x < WIN_W && y < WIN_H)
		data->position->pov = data->position->pov + (x - mouse_x)/2;
	else if (x < mouse_x && x < WIN_W && y < WIN_H)
		data->position->pov = data->position->pov + (x - mouse_x)/2;
	if	(data->position->pov < 0)
		data->position->pov += 360;
	else if(data->position->pov > 360)
		data->position->pov -= 360;
	mouse_x = x;
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

int keypress (int  keycode, t_data *data)
{
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
	return 0;
}


