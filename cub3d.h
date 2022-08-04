#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_map{
	int		map_h;
	int		map_w;
	int		px;
	int		py;
	int		error;
	char	**map_tab;
}	t_map;
#endif
	