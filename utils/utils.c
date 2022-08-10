#include "../headers/cub3d.h"

int	ft_is_whitespace(char c)
{
	if(c == ' ' || c == '\t' || c == '\v' ||
		c == '\v' || c == '\f' || c == '\r')
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

int	ft_is_alpha(const char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char *ft_substr(char *line, int from, size_t len)
{
	int i;
	char *res;

	i = 0;
	if(!len)
		len = ft_strlen(line);
	res = malloc(sizeof(char) * len + 1);
	while(i < len)
	{
		res[i] = line[i];
		i++;
	}
	return (res);
}
