#include "../headers/cub3d.h"

int	ft_is_whitespace(int c)
{
	if(c == ' ' || c == '\t' || c == '\v' ||
		c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

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

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if(!s)
		return (0);
	while(s[i])
		i++;
	return (i);
}

char *ft_substr(char *line, int from, size_t len)
{
	size_t i;
	char *res;

	i = 0;
	if(!len)
		len = ft_strlen(line);
	res = malloc(sizeof(char) * len + 1);
	while(i < len)
	{
		res[i] = line[from + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_strchr(char c, char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if(s[i] == c)
			return (0);
		i++;
	}
	return (0);
}

void	ft_print(char *s)
{
	write(1,&s[0],ft_strlen(s));
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	char	*p;
	int		size1;
	int		size2;
	int		sizep;

	i = 0;
	size1 = ft_strlen((char *)s1);
	size2 = ft_strlen((char *)s2);
	sizep = size1 + size2;
	p = malloc(sizep + 1);
	if (!p)
		return (0);
	while (i < sizep)
	{
		if (i < size1)
			p[i] = s1[i];
		if (i < size2)
			p[i + size1] = s2[i];
		i++;
	}
	p[i] = 0;
	return (p);
}

char	**ft_split(char *s, char c)
{
	char	**splited;
	int		row;
	int		i;
	int		from;

	i = 0;
	row = 0;
	while(s[i])
		if(s[i++] == c)
			row++;
	if(s[ft_strlen(s) - 1] != c)
		row++;
	splited = malloc(sizeof(char) * row + 1);
	splited[row] = 0;
	i = 0;
	from = 0;
	while(i < row)
	{
		if(ft_first_occ(s + from, c) != -1)
			splited[i] = ft_substr(s, from, ft_first_occ(s + from, c)+1);
		else
			splited[i] = ft_substr(s, from, 0);
		// printf("from = %d\n", from);
		from += ft_first_occ(s + from , c) + 1;
		// printf("splited line[n] = %s", splited[i]);
		i++;
	}
	return (splited);
}

int ft_first_occ(char *s, char c)
{
	int	i;

	i = 0;
	while(s[i])
		if(s[i++] == c)
			return (i - 1);
	return (-1);
}