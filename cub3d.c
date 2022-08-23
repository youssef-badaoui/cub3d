/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:30:15 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/23 15:38:24 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

int start_exec(t_map *map)
{
	t_table 	table;
	t_position	position;
	t_ray		rays[N_RAY];
	t_data		data;

	full_data(&data, &table, &position, rays);
	data.map = map;
	create_trigonometric_tables(6480, &table);
	init_player_position(map, &position);
	casting_rays(&table, &rays[0], position);
	drawing(&data);
	return (1);
}

int main(int ac, char **av)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if(!init_map(av, ac, map))
		return (0);
	if(!check_and_stor(ac, av, map))
		return (ft_print("-------->$ ERROR: Error While Parsing\n+++NOTE: check map and try again....\n"), 0);
	ft_print("parsing: OK\n");
	start_exec(map);
	return (1);
}
