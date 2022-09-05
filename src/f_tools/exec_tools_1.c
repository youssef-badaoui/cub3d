#include "../../headers/cub3d.h"

void	create_trigonometric_tables(int narc, t_table *table)
{
	int		i;
	double	angle;
	double	ang_in;
	double	*tan_res;
	double	*sin_res;
	double	*cos_res;

	i = 0;
	ang_in = ANG_IN_D * M_PI/180.0;
	tan_res = malloc(sizeof(double) * narc);
	sin_res = malloc(sizeof(double) * narc);
	cos_res = malloc(sizeof(double) * narc);
	while (i < narc)
	{
		angle = i * ang_in;
		tan_res[i] = tan(angle);
		cos_res[i] = cos(angle);
		sin_res[i] = sin(angle);
		i++;
	}
	table->tan_table = tan_res;
	table->cos_table = cos_res;
	table->sin_table = sin_res;
}

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
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "call of duty");
	mlx->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);	
}

void	get_texters(t_data *data)
{
	data->mlx->texters.N_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[0], &data->mlx->texters.N_img.x, &data->mlx->texters.N_img.y);
	data->mlx->texters.N_img.addr = (int *)mlx_get_data_addr(data->mlx->texters.N_img.img, &data->mlx->texters.N_img.bits_per_pixel, &data->mlx->texters.N_img.line_length, &data->mlx->texters.N_img.endian);
	data->mlx->texters.S_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[1], &data->mlx->texters.S_img.x, &data->mlx->texters.S_img.y);
	data->mlx->texters.S_img.addr = (int *)mlx_get_data_addr(data->mlx->texters.S_img.img, &data->mlx->texters.S_img.bits_per_pixel, &data->mlx->texters.S_img.line_length, &data->mlx->texters.S_img.endian);
	data->mlx->texters.W_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[2], &data->mlx->texters.W_img.x, &data->mlx->texters.W_img.y);
	data->mlx->texters.W_img.addr = (int *)mlx_get_data_addr(data->mlx->texters.W_img.img, &data->mlx->texters.W_img.bits_per_pixel, &data->mlx->texters.W_img.line_length, &data->mlx->texters.W_img.endian);
	data->mlx->texters.E_img.img = mlx_xpm_file_to_image(data->mlx->mlx,data->map->meta_data[3], &data->mlx->texters.E_img.x, &data->mlx->texters.E_img.y);
	data->mlx->texters.E_img.addr = (int *)mlx_get_data_addr(data->mlx->texters.E_img.img, &data->mlx->texters.E_img.bits_per_pixel, &data->mlx->texters.E_img.line_length, &data->mlx->texters.E_img.endian);
}
