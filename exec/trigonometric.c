/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Trigonometric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:00:35 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/12 13:22:09 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	creat_trigonometric_tables(int narc, t_table *table)
{
	int		i;
	double	angle;
	double	ang_in;
	double	cos_res[narc];
	double	sin_res[narc];

	i = 0;
	ang_in = 360.0 / (double)narc;
	ang_in *= M_PI/180;
	while (i < narc)
	{
		angle = i * ang_in;
		printf("angle[%d]: %lf\n", i, angle);
		cos_res[i] = cos(angle);
		sin_res[i] = sin(angle);
		i++;
	}
	table->cos_table = &cos_res[0];
	table->sin_table = &sin_res[0];
}


int	main ()
{
	int	i = 0;
	t_table table;

	creat_trigonometric_tables(1000, &table);
	printf("cos			sin\n");
	while (i < 10000)
	{
		printf("%d %lf		%lf\n", i, table.cos_table[i], table.sin_table[i]);
		i++;
	}
	// printf("%f\n", cos(1));
}