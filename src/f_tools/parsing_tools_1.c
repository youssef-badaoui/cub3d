#include "../../headers/cub3d.h"

int	check_color(char *color, int pos)
{
	int i;

	i = 0;
	while(color[i])
	{
		if(color[i] < '0' || color[i] > '9')
		{
			if(color[i+1] || color[i] != ',')
				return (0);
			else
				if(pos > 1)
					return (0);
		}
		i++;
	}
	return (1);
}

int	check_line(char **map, char *s, int row, int map_h)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if(ft_strchr(s[i], "NSWECO0"))
		{
			if(row == 0 || row == map_h - 1 || i == 0)
				return(0);
			if(!ft_strchr(map[row - 1][i], "NSEW01CO") || 
			!ft_strchr(map[row + 1][i], "NSEW01CO") )
			{
				// printf("here         %s next_line = %s\n", s, map[row + 1]);
				return (0);
			}
		}
		else if (s[i] != '1' && !ft_is_whitespace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_mapex(t_map *map)
{
	int		len;
	char	*name;

	len = ft_strlen(map->map_name);
	name = map->map_name;
	if(name[len - 1] != 'b' || name[len - 2] != 'u' || name[len - 3] != 'c' || name[len - 4] != '.')
		return (0);
	return (1);
}

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

int	ft_get_path(char *line, int from, int meta_type, t_map *map)
{
	int i;
	int len;
	
	i = 0;
	len = 0;
	if(meta_type >= NO && meta_type <= EA)
		from += 2;
	else
		from += 1;
	if(!ft_is_whitespace(line[from]))
		return (0);
	while(ft_is_whitespace(line[from + i]))
		i++;
	from += i;
	while(!ft_is_whitespace(line[from+len]))
		len++;
	if(map->meta_data[meta_type])
		return (0);
	map->meta_data[meta_type] = ft_substr(line, from, len);
	while(line[from+len])
	{
		if(!ft_is_whitespace(line[from+len]))
			return (0);
		len++;
	}
	return (1);
}

