/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/11 09:15:07 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

// static int store(int fd, t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	while(i < map->map_h)
// 	{
		
// 	}
// }

static int	get_meta_data(int fd, t_map *map)
{
	char	*line;
	size_t		i;
	int		from;
	int		meta_type;

	i = 6;
	while(i)
	{
		line = gnl(fd);
		if(!line)
			return (0);
		if (ft_is_meta(line) >= 0)
		{
			from = ft_is_meta(line);
			meta_type = ft_get_meta_type(line, from);
			if (meta_type >= NO && meta_type <= EA)
				from += 3;
			else
				from += 2;				
			map->meta_data[meta_type] = ft_substr(line, from, 0);
			i--;
		}
		else if (!ft_is_empty(line))
			return (free(line), 0);
		free (line);
	}
	return (1);
}

static int	inspect(int fd, t_map *map)
{
	char *line;
	int we_start;

	we_start = 0;
	if(!get_meta_data(fd, map))
		return (0);
	printf("meta done\n");
	while(1)
	{
		line = gnl(fd);
		if(!line)
			break;
		if(!ft_is_empty(line) && !we_start)
			we_start = 1;
		if(ft_is_empty(line) && we_start)
			return (free(line),0);
		ft_find_player(line, map);
		if(!line)
			break;
		if (map->map_w < ft_strlen(line))
			map->map_w = ft_strlen(line);
		map->map_h++;
	}
	printf("map_h = %d map_w = %d map_fl = %d pn = %d px = %d py = %d \n", 
	map->map_h, map->map_w, map->map_fl, map->pn, map->px, map->py);
	return (1);
}

static int check_and_stor(int ac, char **av, t_map *map)
{
	int	fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	printf("fd = %d\n", fd);
	if (fd == -1)
		return (0);
	inspect(fd, map);
	// store(fd, map);
	return (1);
}

int main(int ac, char **av)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	init_map(map);
	if(!check_and_stor(ac, av, map))
		return (0);
	return (1);
}
