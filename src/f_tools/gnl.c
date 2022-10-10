/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:27 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/10/03 11:32:21 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;
	int		l;

	l = ft_strlen(s);
	i = 0;
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	while (s[i] && i < l)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gnl(int fd)
{
	int		i;
	int		nbyte;
	char	buf;
	char	buffer[1000000];

	buffer[0] = 0;
	i = 0;
	if (fd < 0)
		return (NULL);
	while ((nbyte = read(fd, &buf, 1)) && nbyte > 0)
	{
		buffer[i++] = buf;
		buffer[i] = '\0';
		if (buf == '\n')
			return (ft_strdup(buffer));
	}
	if (buffer[0] == 0)
		return (NULL);
	return (ft_strdup(buffer));
}