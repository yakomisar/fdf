
void    dda_line(int x1, int y1, int x2, int y2, fdf *data)
{
	int		delta_x;
	int		delta_y;
	float	x_inc;
	float	y_inc;
	int		step;
	int		i;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	i = 0;
	if (abs(delta_x) > abs(delta_y))
		step = abs(delta_x);
	else
		step = abs(delta_y);
	
	x_inc = delta_x / step;
	y_inc = delta_y / step;
	while (i <= step)
	{
		mlx_pixel_put(data->mlx, data->window, x1, y1, 0x00FF0000);
		x1 = x1 + x_inc;
		y1 = y1 + y_inc;
		i++;
	}
}