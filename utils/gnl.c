/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:27 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/04 18:30:47 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

char	*get_next_line(int fd)
{
	int 	i;
	int		nbyte;
	char	buf;
	char	buffer[1000000];

	buffer[0] = 0;
	i = 0;
	if (fd < 0)
		return (NULL);
	while ((nbyte = read(fd, &buf, 1)) && nbyte > 0)
	{
		buffer[i++] = buf[0];
		buffer[i] = '\0';
		if (buf[0] == '\n')
			return (ft_strdup(buffer));
	}
	if (buffer[0] == 0)
		return (NULL);
	return (ft_strdup(buffer));
}