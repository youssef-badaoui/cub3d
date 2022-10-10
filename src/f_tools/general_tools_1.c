/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tools_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:41 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/05 12:21:43 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
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
	free ((void *)s1);
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
	while (s[i])
		if (s[i++] == c)
			row++;
	if (s[ft_strlen(s) - 1] != c)
		row++;
	splited = malloc(sizeof(char *) * row + 1);
	i = 0;
	from = 0;
	while (i < row)
	{
		if (ft_first_occ(s + from, c) != -1)
			splited[i++] = ft_substr(s, from, ft_first_occ(s + from, c) + 1);
		else
			splited[i++] = ft_substr(s, from, 0);
		from += ft_first_occ(s + from, c) + 1;
	}
	splited[row] = 0;
	return (free(s), splited);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		||str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 43)
			j = 1;
		else
			j = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	return (nb * j);
}
