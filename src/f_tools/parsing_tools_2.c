/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:22:15 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/05 12:22:16 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	ft_is_meta(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_is_alpha(line[i]))
		{
			if (!ft_strncmp(line + i, "NO", 2)
				|| !ft_strncmp(line + i, "SO", 2)
				|| !ft_strncmp(line + i, "WE", 2)
				|| !ft_strncmp(line + i, "EA", 2)
				|| line[i] == 'F' || line[i] == 'C')
				return (i);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}
