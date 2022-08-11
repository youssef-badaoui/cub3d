#include "../headers/cub3d.h"

int ft_first_occ(char *s, char c)
{
	int	i;

	i = 0;
	while(s[i])
		if(s[i++] == c)
			return (i - 1);
	return (-1);
}

int main()
{
    char s[] = "heeereey\nweeweewew";
    printf("%d\n", ft_first_occ(s+0, '\n'));
}