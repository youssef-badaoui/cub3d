#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!init_map(av, ac, map))
		return (0);
	if (!check_and_stor(ac, av, map))
	{
		ft_print("-------->$ ERROR: Error While Parsing\n");
		ft_print("+++NOTE: check map and try again....\n");
		return (0);
	}
	ft_print("parsing: OK\n");
	start_exec(map);
	return (1);
}
