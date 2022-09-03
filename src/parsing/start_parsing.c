#include "../../headers/cub3d.h"

int init_map(char **av, int ac, t_map *map)
{
	if(ac != 2)
		return (0);
	map->map_h = 0;
	map->map_w = 0;
	map->px = 0;
	map->py = 0;
	map->pn = 0;
	map->map_name = av[1];
	map->meta_data[0] = NULL;
	map->meta_data[1] = NULL;
	map->meta_data[2] = NULL;
	map->meta_data[3] = NULL;
	map->meta_data[4] = NULL;
	map->meta_data[5] = NULL;
	return (1);
}

int check_and_stor(int ac, char **av, t_map *map)
{
	int	fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	if(!store(fd, map))
		return (0);
	if(!inspect(map))
		return (0);
	return (1);
}