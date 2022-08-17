#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(t_data *data,int x0, int y0,int x1, int y1)
{

	int t=350;
	int dx, dy, p, x, y;  
	dx=x1-x0;  
	dy=y1-y0;  
	x=x0;  
	y=y0;  
	p=2*dy-dx;  
	while(x<x1)  
	{  
		if(p>=0)  
		{
			my_mlx_pixel_put(&data,x,y, 0x00FF0000);
			// mlx_pixel_put(mlx, win, x,y,0x00FF0000);
			y=y+1;  
			p=p+2*dy-2*dx;  
		}  
		else  
		{  
			my_mlx_pixel_put(&data,x,y,0x00FF0000);
			// mlx_pixel_put(mlx, win, x,y,0x00FF0000);
			p=p+2*dy;}  
			x=x+1;  
			sleep(1);
		}
}

int main()
{
	void *mlx;
	void *win;
	t_data data;
	int tab[8]; 

	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "hello world");
	data.img = mlx_new_image(mlx, 500,500);
	data.addr = mlx_get_data_addr(data.img,&data.bits_per_pixel,&data.line_length,&data.endian);
	draw_line();
	mlx_put_image_to_window(mlx,win,data.img,0,0);
	printf("hey\n");
	mlx_loop(mlx);
}