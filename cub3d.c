/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/11 15:05:38 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

// static int inspect(int fd, t_map *map)
// {
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

static int	store(int fd, t_map *map)
{
	char	*line;
	char	*map_string;
	int i = 0;

	if(!get_meta_data(fd, map))
		return (0);
	while(1)
	{
		line = gnl(fd);
		if(!line)
			break;
		map_string  = ft_strjoin(map_string, line);
		free(line);
	}
	ft_map_clean(map_string);
	map->map_tab = ft_split(map_string, '\n');
	while(map->map_tab[i])
	{
		ft_print(map->map_tab[i++]);
	}
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
	store(fd, map);
	// inspect(fd, map);     
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
