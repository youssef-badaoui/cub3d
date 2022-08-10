/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/10 16:37:58 by ybadaoui         ###   ########.fr       */
=======
/*   Updated: 2022/08/10 14:50:32 by ybadaoui         ###   ########.fr       */
>>>>>>> 1ac9d7a2987667fdb09ea4ccef579a60a5e882a1
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

static int store(int fd, t_map *map)
{
	int	i;

	i = 0;
	while(i < map->map_h)
	{
		
	}
}

static int	get_meta_data(int fd, t_map *map)
{
	char	*line;
	int		i;
	int		from;
	int		meta_type;

	while(i < 6)
	{
		line = gnl(fd);


		if (ft_is_meta(line))
		{
			from = ft_is_meta(line);
			meta_type = ft_get_meta_type(line, from);
			if (meta_type >= NO && meta_type <= EA)
				from += 3;
			else
				from += 2;				
			map->meta_data[meta_type] = ft_substr(line, from, NULL);
		}
		i++;
=======
		if(str)
		
>>>>>>> 1ac9d7a2987667fdb09ea4ccef579a60a5e882a1
	}
}

static int	inspect(int fd, t_map *map)
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

static int check_and_stor(int ac, char **av, t_map *map)
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

	init_map(map);
	if(!check_and_stor(ac, av, map))
		return (0);
}
