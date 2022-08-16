/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/16 13:02:56 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

static int inspect(t_map *map)
{
	char	**tab;

	tab = map->map_tab;
	ft_get_data(map);
	if(!ft_check_map(map))
		return (0);
	return (1);
}

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
		if (ft_is_meta(line) > -1)
		{
			from = ft_is_meta(line);
			meta_type = ft_get_meta_type(line, from);
			if(!ft_get_path(line, from, meta_type, map))
				return (0);
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

	map_string = NULL;
	if(!get_meta_data(fd, map))
		return (0);
	if(!get_colors(map))
		return (0);
	while(1)
	{
		line = gnl(fd);
		if(!line)
			break ;
		map_string  = ft_strjoin(map_string, line);
		free(line);
	}
	map_string = ft_map_clean(map_string);
	map->map_tab = ft_split(map_string, '\n');
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
	if(!store(fd, map))
		return (0);
	if(!inspect(map))
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if(!init_map(av, ac, map))
		return (0);
	if(!check_and_stor(ac, av, map))
		return (ft_print("-------->$ ERROR: Error While Parsing\n+++NOTE: check map and try again....\n"), 0);
	befor_exec(map);
	ft_print("parsing: OK\n");
	return (1);
}
