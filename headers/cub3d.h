/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:23 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/14 09:52:53 by ybadaoui         ###   ########.fr       */
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

#endif
	