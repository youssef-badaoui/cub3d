/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:32:19 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/10/10 16:38:22 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;

	if (!init_map(av, ac, &map))
		return (0);
	if (!check_and_stor(ac, av, &map))
	{
		ft_print("-------->$ ERROR: Error While Parsing\n");
		ft_print("+++NOTE: check map and try again....\n");
		return (0);
	}
	ft_print("parsing: OK\n");
	start_exec(&map);
	return (1);
}
