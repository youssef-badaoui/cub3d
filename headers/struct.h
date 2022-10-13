/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:30 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/10/13 14:21:40 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define INTERSECTION_FOUND 1
# define DOOR_FOUND 2
# define CELL_SIZE 500
# define FOV 60
# define HALF_FOV 30
# define ANG_IN_D 0.05555555555
# define N 0
# define E 90
# define S 180
# define W 270
# define WIN_W 1080
# define WIN_H 520
# define N_RAY WIN_W
# define OPEN 3
# define CLOSE 4

enum e_meta_type
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
	char			**map_tab;
	char			*map_name;
	int				map_h;
	int				map_w;
	int				map_vh;
	int				map_vw;
	int				pn;
	int				px;
	int				py;
	int				pv;
	char			*meta_data[6];
	int				flr[3];
	int				cl[3];
	unsigned long	int_f;
	unsigned long	int_c;
}	t_map;

typedef struct s_position
{
	int		x_cell;
	int		y_cell;
	double	virtual_px;
	double	virtual_py;
	double	pov;
	t_map	*map;
}	t_position;

typedef struct s_ray
{
	int			door;
	int			first;
	int			v_skip;
	int			h_skip;
	double		x_save;
	double		y_save;
	double		ray_pov;
	int			index;
	double		xi ;
	double		yi ;
	double		xbound ;
	double		ybound;
	int			v_hit;
	int			h_hit;
	double		v_distance;
	double		h_distance;
	double		x_step;
	double		y_step;
	int			quadrant;
	int			xcell_v;
	int			ycell_v;
	int			xcell_h;
	int			ycell_h;
	double		save_distance;
	double		ray_h;
	t_position	*player;
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
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}	t_texter;

typedef struct s_texters
{
	t_texter	n_img;
	t_texter	s_img;
	t_texter	e_img;
	t_texter	w_img;
	t_texter	o_door;
	t_texter	c_door;
	t_texter	fog;
	t_texter	side;
	t_texter	nt;
}	t_texters;

typedef struct s_mlx
{
	void		*mlx;
	void		*img;
	void		*win;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_texters	texters;
}	t_mlx;

typedef struct s_keystate
{
	int	tir;
	int	w;
	int	a;
	int	s;
	int	d;
	int	r;
	int	l;
	int	q;
	int	esc;
	int	o;
	int	c;
	int	run;
}	t_keystate;

typedef struct s_line_param
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_line_param;

typedef struct s_data
{
	t_mlx			*mlx;
	t_map			*map;
	t_table			*table;
	t_ray			*ray;
	t_position		*position;
	t_keystate		keystate;
	t_line_param	line_param;
	char			*gun[25];
	int				gun_x;
	int				gun_y;
	int				ray_w;
	int				ray_h;
	int				speed;
	int				cell_size;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				e2;
	int				err;
}	t_data;

#endif