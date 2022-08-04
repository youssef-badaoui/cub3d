/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/04 18:32:58 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

int store(int fd, t_map *map)
{
	int	i;

	i = 0;
	while(i < map->map_h)
	{
		
	}
}

void get_meta_data(int fd, t_map *map)
{
	char *line;

	while(1)
	{
		line = gnl(fd);	
	}
}

int	inspect(int fd, t_map *map)
{
	char *line;

	get_meta_data(fd, map);
	while(1)
	{
		line = gnl(fd);
		if(!line)
			break;

		map->map_h++;
	}
}

int check_and_stor(int ac, char **av, t_map *map)
{
	int	fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	inspect(fd, map);
	store(fd, map);
}

int main(int ac, char **av)
{
	t_map *map;

	if(!check_and_stor(ac, av, map))
		return (0);
}