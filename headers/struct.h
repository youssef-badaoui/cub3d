/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:30 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/13 21:11:21 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define CELL_SIZE = 16

enum meta_type
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	F = 4,
	C = 5
};

typedef struct s_table
{
	long double	*cos_table;
	long double	*sin_table;
}				t_table;

typedef struct s_map
{
	char	**map_tab;
	int		map_h;	//map high
	int		map_w; 	//map width 
	int		pn; 	//player number;
	int		px; 	//player x;
	int		py; 	//player y;
	char	*meta_data[6];
	int		F[3];
	int		C[3];
}	t_map;

#endif