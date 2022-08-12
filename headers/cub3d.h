/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:16:23 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/08/12 12:21:27 by Ma3ert           ###   ########.fr       */
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
int		init_map(t_map *map);
void	ft_find_player(char *line, t_map *map);
int		ft_strchr(char c, char *s);
void	ft_print(char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_map_clean(char *map_string);
int		ft_first_occ(char *s, char c);
char	**ft_split(char *s, char c);

#endif
	