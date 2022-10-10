/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:32:40 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/10 16:32:43 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	ft_meta_check(char **meta)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		fd = open(meta[i], O_RDONLY);
		if (fd < 0)
			return (0);
		close(fd);
		i++;
	}
	return (1);
}

int	ft_check_map(t_map *map)
{
	int	row;

	row = 0;
	if (!ft_meta_check(map->meta_data) || !check_mapex(map))
		return (0);
	if (map->pn != 1)
		return (0);
	while (map->map_tab[row])
	{
		if (!check_line(map->map_tab, map->map_tab[row], row, map->map_h))
			return (0);
		row++;
	}
	return (1);
}

void	ft_find_player(char *line, t_map *map)
{
	int			x;
	static int	y;

	x = 0;
	while (line[x])
	{
		if (ft_strchr(line[x], "NSEW"))
		{
			map->px = x;
			map->py = y;
			map->pv = line[x];
			map->pn++;
		}
		x++;
	}
	y++;
}

void	ft_get_data(t_map *map)
{
	int		i;
	char	**tab;

	i = 0;
	tab = map->map_tab;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > map->map_w)
			map->map_w = ft_strlen(tab[i]);
		ft_find_player(tab[i], map);
		map->map_h++;
		i++;
	}
	map->map_vh = map->map_h * CELL_SIZE;
	map->map_vw = map->map_w * CELL_SIZE;
}

int	inspect(t_map *map)
{
	char	**tab;

	tab = map->map_tab;
	ft_get_data(map);
	if (!ft_check_map(map))
		return (0);
	return (1);
}
