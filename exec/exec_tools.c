#include "../headers/cub3d.h"
#include "../headers/struct.h"

void    init_player_position(t_map *map, t_position *pp)
{
    pp->x_cell = map->px;
    pp->y_cell = map->py;
    pp->virtual_px = pp->x_cell * CELL_SIZE + CELL_SIZE / 2;
    pp->virtual_py = pp->y_cell * CELL_SIZE + CELL_SIZE / 2;
    pp->pov =  
}