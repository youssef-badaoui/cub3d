#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

enum meta_type
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	F = 4,
	C = 5
};

typedef struct s_map{
	char	**map_tab;
	int		map_h;//map high
	int		map_w; //map width 
	int		pn; //player number;
	int		px; //player x;
	int		py; //player y;
	int		error; //this will be changed to 1 if an error occured in the parsing to check it after;
	char	*meta_data[6];
}	t_map;

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
	