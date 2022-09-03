#include "../headers/cub3d.h"

void	mini_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while(i < data->map->map_h)
	{
		j = 0;
		while(data->map->map_tab[i][j])
		{
			if(data->map->map_tab[i][j] == '1')
				ft_color_image(data->mlx,  0x7b7d7d  , i, j);
			else if	(data->map->map_tab[i][j] == '0' || ft_strchr(data->map->map_tab[i][j], "NSEW"))
				ft_color_image(data->mlx,   0x58d68d , i, j);
			j++;
		}
		i++;
	}
}

void drawing(t_data *data)
{
	void *img;
	static double i;
	int x;
	int y;

	casting_rays(data->table, data->ray, *data->position);
	// mini_map(data);
	ft_color_win(data->mlx, 0x0);
	ft_3d(data);
	mlx_put_image_to_window(data->mlx->mlx,data->mlx->win, data->mlx->img, 0,0);
	img = mlx_xpm_file_to_image(data->mlx->mlx, data->gun[(int)i],&x, &y);
	if(!data->keystate.w)
		img = mlx_xpm_file_to_image(data->mlx->mlx, data->gun[0],&x, &y);
	if(data->keystate.tir == 0)
		mlx_put_image_to_window(data->mlx->mlx,data->mlx->win, img, WIN_W - x, WIN_H-y);
		i+= 0.1;
	if(i > 2 && i < 8)
		i = 8;
	if(i > 11)
		i = 0;
}