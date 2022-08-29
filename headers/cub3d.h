/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:23 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/28 13:35:15 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

char	*ft_strdup(char *s);
int		ft_strlen(char *s);
char	*gnl(int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_is_alpha(const char c);
int		ft_is_meta(const char *line);
int		ft_is_empty(const char *line);
int		ft_is_whitespace(int c);
char	*ft_substr(char *line, int from, size_t len);
int		ft_get_meta_type(char *line, int from);
int		init_map(char **av, int ac, t_map *map);
void	ft_find_player(char *line, t_map *map);
int		ft_strchr(char c, char *s);
void	ft_print(char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_map_clean(char *map_string);
int		ft_first_occ(char *s, char c);
char	**ft_split(char *s, char c);
void	ft_get_data(t_map *map);
int		ft_check_map(t_map *map);
int		get_colors(t_map *map);
int		ft_tablen(char **tab);
void	f_tab(char **tab);
int		ft_atoi(const char *str);
int		check_line(char **map, char *s, int row, int map_h);
int	    ft_get_path(char *line, int from, int meta_type, t_map *map);
int 	check_color(char *color, int pos);
int	    check_mapex(t_map *map);
void	ft_draw_ray(t_data *data, int i);
void    full_data(t_data *data, t_table *table, t_position *position, t_ray *ray);
void    init_player_position(t_map *map, t_position *pp);
void	drawing(t_data *data);
void	ft_draw_map(t_data *data);
void	ft_color_image(t_mlx *mlx,  int color, int i, int j);
void	ft_mlx_put_px(t_mlx *mlx, int x, int y, unsigned int color);
int		start_exec(t_map *map);
void	casting_rays(t_table *table, t_ray *rays, t_position position);
double	calcul_adjacent(double hypotenuse, double opposite);
double	calcul_opposite(double hypotenus, double adjacent);
void	create_trigonometric_tables(int narc, t_table *table);
int 	check_and_stor(int ac, char **av, t_map *map);
void	send_ray(t_table *table, t_ray *ray, t_position position);
void	triangle_sides(t_ray *ray, t_position position, t_table *table);
void	ft_line_formula(double x, double y, t_position *position);

#endif
	