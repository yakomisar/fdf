#include "fdf.h"

void    dda_line(int x1, int y1, int x2, int y2, fdf *data)
{
	int		delta_x;
	int		delta_y;
	float	x_inc;
	float	y_inc;
	int		step;
	int		i;
    float   x;
    float   y;

	x1 *= 20;
	x2 *= 20;
	y1 *= 20;
	y2 *= 20;
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	i = 0;
    x = (float)x1;
    y = (float)y1;
	if (abs(delta_x) > abs(delta_y))
		step = abs(delta_x);
	else
		step = abs(delta_y);
	
	x_inc = (float)delta_x / (float)step;
	y_inc = (float)delta_y / (float)step;
	while (i <= step)
	{
		mlx_pixel_put(data->mlx, data->window, (int)x, (int)y, 0x00FF0000);
		x = x + x_inc;
		y = y + y_inc;
		i++;
	}
}

void	draw_map(fdf *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x != data->width - 1)
				dda_line(x, y, x + 1, y, data);	
			if (y != data->height - 1)
				dda_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}