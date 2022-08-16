/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:30 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/16 13:29:34 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define CELL_SIZE = 16
# define FOV = 60
# define N_RAY = 1080

enum meta_type
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	F = 4,
	C = 5
};

enum player_v
{
	N = 0;
	S = 180;
	
};



typedef	struct s_position
{
	int		x_cell;			// x cord of the cell 
	int		y_cell;			// y cord of the cell
	int		virtual_px;		// x cord of the player in the virtual dimension
	int		virtual_py;		// y cord of the player in the virtual dimension
	double	pov;			// the point of view (obviously an angle)
}				t_position;

typedef struct s_ray
{
	double		angle;		// angle of the ray
	int			xi;			// the x cord of the verticatl intersection
	int			yi;			// the y cord of the horizontal intersection
	int			xpound;		// the x cord of the horizontal intersection 
	int			ypound;		// the y cord of the vertical intersection
	int			x_hit;		// the type of the cell the xray intersect with 
	int			y_hit;		// the type of the cell the yray intersect with
	int			v_distance;	// the distance between the position of the player
	int			h_distance;	// and the intesection
	t_position	*player;	// info about the position of the player
}				t_ray;


typedef struct s_table
{
	double	*tan_table;
}				t_table;

typedef struct s_map
{
	char	**map_tab;
	char	*map_name;
	int		map_h;	//map high
	int		map_w; 	//map width 
	int		pn; 	//player number;
	char	pv; 	//player vision;
	int		px; 	//player x;
	int		py; 	//player y;
	char	*meta_data[6];
	int		F[3];
	int		C[3];
}	t_map;

#endif