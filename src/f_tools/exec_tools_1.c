#include "../../headers/cub3d.h"

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

void full_data(t_data *data, t_table *table, t_position *position, t_ray *ray)
{
	data->table = table;
	data->ray = ray;
	data->position = position;
	data->ray_h = 0;
}

void	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);	
}

void	get_texters(t_data *data)
{
	t_texters *t;

	t = &data->mlx->texters;
	t->N_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[0], &t->N_img.x, &t->N_img.y);
	t->N_img.addr = (int *)mlx_get_data_addr(t->N_img.img, &t->N_img.bits_per_pixel, &t->N_img.line_length, &t->N_img.endian);
	t->S_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[1], &t->S_img.x, &t->S_img.y);
	t->S_img.addr = (int *)mlx_get_data_addr(t->S_img.img, &t->S_img.bits_per_pixel, &t->S_img.line_length, &t->S_img.endian);
	t->W_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[2], &t->W_img.x, &t->W_img.y);
	t->W_img.addr = (int *)mlx_get_data_addr(t->W_img.img, &t->W_img.bits_per_pixel, &t->W_img.line_length, &t->W_img.endian);
	t->E_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[3], &t->E_img.x, &t->E_img.y);
	t->E_img.addr = (int *)mlx_get_data_addr(t->E_img.img, &t->E_img.bits_per_pixel, &t->E_img.line_length, &t->E_img.endian);
	t->C_door.img = mlx_xpm_file_to_image(data->mlx->mlx,"./wall_texters/code.xpm", &t->C_door.x, &t->C_door.y);
	t->C_door.addr = (int *)mlx_get_data_addr(t->C_door.img, &t->C_door.bits_per_pixel, &t->C_door.line_length, &t->C_door.endian);
	t->O_door.img = mlx_xpm_file_to_image(data->mlx->mlx,"./wall_texters/ooo.xpm", &t->O_door.x, &t->O_door.y);
	t->O_door.addr = (int *)mlx_get_data_addr(t->O_door.img, &t->O_door.bits_per_pixel, &t->O_door.line_length, &t->O_door.endian);
	t->fog.img = mlx_xpm_file_to_image(data->mlx->mlx,"./wall_texters/fog.xpm", &t->fog.x, &t->fog.y);
	t->fog.addr = (int *)mlx_get_data_addr(t->fog.img, &t->fog.bits_per_pixel, &t->fog.line_length, &t->fog.endian);
	t->side.img = mlx_xpm_file_to_image(data->mlx->mlx,"./wall_texters/side.xpm", &t->side.x, &t->side.y);
	t->side.addr = (int *)mlx_get_data_addr(t->side.img, &t->side.bits_per_pixel, &t->side.line_length, &t->side.endian);
	t->nt.img = mlx_xpm_file_to_image(data->mlx->mlx,"./wall_texters/nt.xpm", &t->nt.x, &t->nt.y);
	t->nt.addr = (int *)mlx_get_data_addr(t->nt.img, &t->nt.bits_per_pixel, &t->nt.line_length, &t->nt.endian);
}
