/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/10 19:57:55 by ybadaoui         ###   ########.fr       */
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
		printf(" is meta = %d\n",ft_is_meta(line));
		if (ft_is_meta(line) >= 0)
		{
			printf("line = %s\n", line);
			from = ft_is_meta(line);
			meta_type = ft_get_meta_type(line, from);
			if (meta_type >= NO && meta_type <= EA)
				from += 3;
			else
				from += 2;				
			map->meta_data[meta_type] = ft_substr(line, from, 0);
			i--;
		}
		else if(!ft_is_empty(line))
			return (0);
	}
	return (1);
}

static int	inspect(int fd, t_map *map)
{
	// char *line;

	get_meta_data(fd, map);
	// while(1)
	// {
	// 	line = gnl(fd);
	// 	if(!line)
	// 		break;

	// 	map->map_h++;
	// }
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
