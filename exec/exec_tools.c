#include "../headers/cub3d.h"
#include "../headers/struct.h"

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

void	ft_mlx_put_px(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = y * mlx->line_length + x * (mlx->bits_per_pixel / 8);
	dst = color;
}