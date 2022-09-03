/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:30 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/09/03 11:53:12 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define INTERSECTION_FOUND 1
# define CELL_SIZE 100
# define FOV 60
# define HALF_FOV 30
# define ANG_IN_D 0.05555555555
# define N 0
# define E 90
# define S 180
# define W 270
# define WIN_W 1080
# define WIN_H 524
# define N_RAY WIN_W

enum meta_type
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	F = 4,
	C = 5
};


typedef struct s_map
{
	char	**map_tab;
	char	*map_name;
	int		map_h;			// map high
	int		map_w;	 		// map width 
	int		map_vh;			// map virtual high
	int		map_vw;	 		// map virtual width 
	int		pn; 			// player number;
	int		px; 			// player x;
	int		py; 			// player y;
	int		pv;				// player vision;
	char	*meta_data[6];
	int		F[3];
	int		C[3];
}	t_map;

typedef	struct s_position
{
	int		x_cell;			// x cord of the cell 
	int		y_cell;			// y cord of the cell
	double		virtual_px;		// x cord of the player in the virtual dimension
	double		virtual_py;		// y cord of the player in the virtual dimension
	double	pov;			// the point of view (obviously an angle)
	t_map	*map;			// the map
}				t_position;

typedef struct s_ray
{
	int			first;		// which intersection is the first
	int			v_skip;		// to skip the vertical calculation
	int			h_skip;		// to skip the horizontal calculation
	double		x_save;		// the x cord of the intersection with a wall
	double		y_save;		// the y cord of the intersection with a wall
	double		ray_pov;	// the point of view of the ray
	int			index;		// the index of angle of the ray
	double		xi ;		// the x cord of the horizontal intersection
	double		yi ;		// the y cord of the vertical intersection
	double		xbound ;	// the x cord of the vertical intersection 
	double		ybound;		// the y cord of the horizontal intersection
	int			v_hit;		// the type of the cell for the vertical intersect
	int			h_hit;		// the type of the cell for the horizontal intersect
	double		v_distance;	// the distance between the position of the player
	double		h_distance;	// and the intesection
	double		x_step;		// step to get to the next x intersection 
	double		y_step;		// step to get to the next y intersection
	int			quadrant;	// in which quadrant the ray is casted
	int			xcell_v;	// the x cord of cell for the vertical intersection
	int			ycell_v;	// the y cord of cell for the vertical intersection 
	int			xcell_h;	// the x cord of cell for the horizontal interesection
	int			ycell_h;	// the y cord of cell for the horizontal interesection
	double		save_distance;
	double		ray_h;
	t_position	*player;	// info about the position of the player
}				t_ray;

typedef struct s_table
{
	double	*tan_table;
	double	*cos_table;
	double	*sin_table;
}				t_table;
typedef struct s_texter
{
	void	*img;
	int 	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
} t_texter;

typedef struct s_texters
{
	t_texter 	N_img;
	t_texter	S_img;
	t_texter	E_img;
	t_texter	W_img;
} t_texters;

typedef struct s_mlx
{
	void	*mlx;
	void	*img;
	void	*win;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_texters texters;
} t_mlx;

typedef struct s_keystate
{
	int tir;
	int w;
	int a;
	int s;
	int d;
	int r;
	int l;
} t_keystate;

typedef struct s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_table		*table;
	t_ray		*ray;
	t_position	*position;
	t_keystate	keystate;
	char		*gun[25];
	int			gun_x;
	int			gun_y;
	int			ray_w;
} t_data;



#endif