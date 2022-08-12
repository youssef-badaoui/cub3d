#include "../headers/cub3d.h"

int	ft_get_meta_type(char *line, int from)
{
	if (!ft_strncmp(line + from, "NO", 2))
		return (NO);
	else if (!ft_strncmp(line + from, "SO", 2))
		return (SO);
	else if (!ft_strncmp(line + from, "WE", 2))
		return (WE);
	else if (!ft_strncmp(line + from, "EA", 2))
		return (EA);
	else if (!ft_strncmp(line + from, "F", 1))
		return (F);
	else if (!ft_strncmp(line + from, "C", 1))
		return (C);
	else
		return (-1);
}

int ft_is_empty(const char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if(!ft_is_whitespace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int ft_is_meta(const char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if(ft_is_alpha(line[i]))
		{
			if(!ft_strncmp(line+i, "NO", 2) ||
				!ft_strncmp(line+i, "SO", 2) ||
				!ft_strncmp(line+i, "WE", 2) || 
				!ft_strncmp(line+i, "EA", 2) || 
				line[i] == 'F' || line[i] == 'C')
					return (i);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

int init_map(t_map *map)
{
	map->map_h = 0;
	map->map_w = 0;
	map->px = 0;
	map->py = 0;
	map->error = 0;
	map->meta_data[0] = NULL;
	map->meta_data[1] = NULL;
	map->meta_data[2] = NULL;
	map->meta_data[3] = NULL;
	map->meta_data[4] = NULL;
	map->meta_data[5] = NULL;
	return (1);
} 

void	ft_find_player(char *line, t_map *map)
{
	int			x;
	static int	y;

	x = 0;
	while(line[x])
	{
		if(ft_strchr(line[x], "NSEW"))
		{
			map->px = x;
			map->py = y;
			map->pn++;
		}
		x++;
	}
	y++;
}

char	*ft_map_clean(char *map_string)
{
	int		start;
	int		end;
	int		i;
	char 	*new_map_string;

	i = 0;
	while (map_string[i] && ft_is_whitespace(map_string[i]))
	{
		if (map_string[i] == 10)
			start = i + 1;
		i++;
	}
	end = ft_strlen(map_string)-1;
	i = end;
	while (i >= 0 && ft_is_whitespace(map_string[i]))
	{
		if (map_string[i] == 10)
			end = i + 1;
		i--;
	}
	new_map_string = ft_substr(map_string, start, end-start);
	free(map_string);
	return(new_map_string);
}

void	ft_find_player(char *line, t_map *map)
{
	int			x;
	static int	y;

	x = 0;
	while(line[x])
	{
		if(ft_strchr(line[x], "NSEW"))
		{
			map->px = x;
			map->py = y;
			map->pn++;
		}
		x++;
	}
	y++;
}

void	ft_get_data(t_map *map)
{
	int	i;
	char	**tab;

	i = 0;
	tab = map->map_tab;
	map->map_h = ft_strlen(tab);
	while(tab[i])
	{
		if(ft_strlen(tab[i]) > map->map_w)
			map->map_w = ft_strlen(tab);
		ft_find_player(tab[i], map);
		i++;
	}
}

int	ft_meta_check(char *meta)
{
	int	i;
	int	fd;

	i = 0;
	while(i < 4)
	{
		fd = open(meta[i], O_RDONLY);
		if(fd < 0)
			return (0,ft_print("Textures path ERROR!!\n"));
		close(fd);
		i++;
	}
	
}

int	get_colors(t_map *map)
{
	char	**c;
	char	**f;
	int		i;

	i = 0;
	c = ft_split(map->meta_data[4]);
	f = ft_split(map->meta_data[5]);
	if(ft_strlen(c) - ft_strlen(f))
		return (0);
	while(i < 3)
	{
		if(!(map->C[i] = ft_atoi(c[i])) || !(map->F[i] = ft_atoi(f[i])))
			return (f_tab(c), f_tab(f), 0);
		i++
	}
	f_tab(c);
	f_tab(f);
}

int	ft_check_map(t_map *map)
{
	int	row;

	row = 0;
	if(!ft_meta_check(map->meta_data))
		return (0);
	while(map->meta_data[row])
	{
		if(!check_line(map->map_tab, map->meta_data[row], row, map->map_h))
			return (0);
	}
	
}

int	check_line(char **map, char *s, int row, int map_h)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if(s[i] == '0')
		{
			if(row == 0 || row == map_h || i == 0)
				return(0,f_print("map not closed\n"));
			if(!ft_strchr(map[row - 1][i], "01") || 
			!ft_strchr(map[row + 1][i], "01") || 
			!ft_strchr(map[row][i+1], "01") || 
			!ft_strchr(map[row][i-1], "01"))
				return(0,f_print("map not closed\n"));
		}
		else if (!ft_strchr(s[i], "	NSEW1"))
			return (0, f_print("strange character in map\n"));
		i++;
	}
}