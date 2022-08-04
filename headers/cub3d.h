#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_map{
	char	**map_tab;
	int		map_h;//map high
	int		map_w; //map width 
	int		px; //player x;
	int		py; //player y;
	int		error; //this will be changed to 1 if an error occured in the parsing to check it after;
	char	*meta_data[6];
	int		F[3];
	int		C[3];
}	t_map;

char	*ft_strdup(char *s);
int		ft_strlen(char *s);
char	*get_next_line(int fd);

#endif
	