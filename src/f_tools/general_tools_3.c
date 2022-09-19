#include "../../headers/cub3d.h"

int ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
		return (i);
}

int	ft_is_alpha(const char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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

int ft_min(int a, int b)
{
	if(a < 0)
		return (b);
	if(b < 0)
		return (a);
	if(a > b)
		return (b);
	return (a);
}

int ft_max(int a, int b)
{
	if(a > b)
		return (a);
	return (b);
}

void f_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		free(tab[i++]);
	free(tab);
}












