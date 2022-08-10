

#include "../headers/cub3d.h"

int	ft_is_whitespace(char c)
{
	if(c == ' ' || c == '\t' || c == '\v' ||
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
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
					return (1);
		}
		i++;
	}

}

int	ft_is_alpha(const char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int i;

	i = 0;
	while(i < n)
	{
		if(s1[i] != s2[i])
			return (s1-s2);
		i++;
	}
	return (0);
}