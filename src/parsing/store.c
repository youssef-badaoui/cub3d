/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:32:54 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/13 14:24:53 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

char	*ft_map_clean(char *map_string)
{
	int		start;
	int		end;
	int		i;
	char	*new_map_string;

	i = 0;
	while (map_string[i] && ft_is_whitespace(map_string[i]))
	{
		if (map_string[i] == 10)
			start = i + 1;
		i++;
	}
	end = ft_strlen(map_string) - 1;
	i = end;
	while (i >= 0 && ft_is_whitespace(map_string[i]))
	{
		if (map_string[i] == 10)
			end = i + 1;
		i--;
	}
	new_map_string = ft_substr(map_string, start, end - start + 1);
	free(map_string);
	return (new_map_string);
}

static int	get_meta_data(int fd, t_map *map)
{
	char	*line;
	size_t	i;
	int		from;
	int		meta_type;

	i = 6;
	while (i)
	{
		line = gnl(fd);
		if (!line)
			return (0);
		if (ft_is_meta(line) > -1)
		{
			from = ft_is_meta(line);
			meta_type = ft_get_meta_type(line, from);
			if (!ft_get_path(line, from, meta_type, map))
				return (0);
			i--;
		}
		else if (!ft_is_empty(line))
			return (free(line), 0);
		free (line);
	}
	return (1);
}

unsigned long	rgbtolong(int *tab)
{
	return (tab[0] << 16 | tab[1] << 8 | tab[2]);
}

int	get_colors(t_map *map)
{
	char	**c;
	char	**f;
	int		i;

	i = 0;
	c = ft_split(map->meta_data[C], ',');
	f = ft_split(map->meta_data[F], ',');
	if (ft_tablen(c) != 3 || ft_tablen(f) != 3)
		return (0);
	while (i < 3)
	{
		if (!check_color(c[i], i) || !check_color(f[i], i))
			return (0);
		map->cl[i] = ft_atoi(c[i]);
		map->flr[i] = ft_atoi(f[i]);
		if (map->cl[i] < 0 || map->cl[i] > 255
			|| map->flr[i] < 0 || map->flr[i] > 255)
			return (0);
		i++;
	}
	map->int_c = rgbtolong(map->cl);
	map->int_f = rgbtolong(map->flr);
	f_tab(c);
	f_tab(f);
	return (1);
}

int	store(int fd, t_map *map)
{
	char	*line;
	char	*map_string;

	map_string = NULL;
	if (!get_meta_data(fd, map))
		return (0);
	if (!get_colors(map))
		return (0);
	while (1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		map_string = ft_strjoin(map_string, line);
		free(line);
	}
	map_string = ft_map_clean(map_string);
	map->map_tab = ft_split(map_string, '\n');
	printf("%p\n", map_string);
	return (1);
}
