#include "../../headers/cub3d.h"

int ft_first_occ(char *s, char c)
{
	int	i;

	i = 0;
	while(s[i])
		if(s[i++] == c)
			return (i - 1);
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

int	ft_is_whitespace(int c)
{
	if(c == ' ' || c == '\t' || c == '\v' ||
		c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	ft_print(char *s)
{
	write(1,&s[0],ft_strlen(s));
}

char *ft_substr(char *line, int from, size_t len)
{
	size_t i;
	char *res;

	i = 0;
	if(!len)
		len = ft_strlen(line + from);
	// printf("len = %zu\n÷", len);
	res = malloc(sizeof(char) * len + 1);
	while(i < len)
	{
		res[i] = line[from + i];
		// printf("copied = %÷c\n", line[from + i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}





