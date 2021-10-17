#include "fdf.h"

void	get_color(fdf *data)
{
	data->z1 = data->z_matrix[data->y1][data->x1];
	data->z2 = data->z_matrix[data->y2][data->x2];
	if (data->z1 || data->z2)
		data->color = 0xe80c0c;
	else
		data->color = 0xffffff;
}

int	get_step(int delta_x, int delta_y)
{
	int	step;

	if (abs(delta_x) > abs(delta_y))
		step = abs(delta_x);
	else
		step = abs(delta_y);
	return (step);
}

void	iso_one(fdf *data)
{
	int	previous_x;
	int	previous_y;

	data->x1 *= data->zoom;
	data->y1 *= data->zoom;
	previous_x = data->x1;
	previous_y = data->y1;
	data->x1 = previous_x * cos(data->my_angle.first);
	data->x1 += (previous_y * cos(data->my_angle.second));
	data->x1 += (data->z1 * cos(data->my_angle.third));
	data->y1 = previous_x * sin(data->my_angle.first);
	data->y1 += (previous_y * sin(data->my_angle.second));
	data->y1 += (-(data->z1) * sin(data->my_angle.third));
}

void	iso_sec(fdf *data)
{
	int	previous_x;
	int	previous_y;

	data->x2 *= data->zoom;
	data->y2 *= data->zoom;
	previous_x = data->x2;
	previous_y = data->y2;
	data->x2 = previous_x * cos(data->my_angle.first);
	data->x2 += (previous_y * cos(data->my_angle.second));
	data->x2 += (data->z2 * cos(data->my_angle.third));
	data->y2 = previous_x * sin(data->my_angle.first);
	data->y2 += (previous_y * sin(data->my_angle.second));
	data->y2 += (-(data->z2) * sin(data->my_angle.third));
}