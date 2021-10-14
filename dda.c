/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:37:49 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/24 19:45:35 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	iso(int *x, int *y, int z, fdf *data)
{
	int		previous_x;
    int		previous_y;
	
	*x *= data->zoom;
	*y *= data->zoom;
	// y1 *= data->zoom;
	// y2 *= data->zoom;
	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(data->my_angle.first);
    *x += (previous_y * cos(data->my_angle.second));
	*x += (z * cos(data->my_angle.third));
	*y = previous_x * sin(data->my_angle.first);
	*y += (previous_y * sin(data->my_angle.second));
	*y += (- z * sin(data->my_angle.third));
}

void	get_color(int z1, int z2, fdf *data)
{
	if (z1 || z2)
		data->color = 0xe80c0c;
	else
		data->color = 0xffffff;
}

int		get_step(int delta_x, int delta_y)
{
	int	step;

	if (abs(delta_x) > abs(delta_y))
		step = abs(delta_x);
	else
		step = abs(delta_y);
	return (step);
}

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
	int		z1;
	int		z2;

	z1 = data->z_matrix[y1][x1];
	z2 = data->z_matrix[y2][x2];
	get_color(z1, z2, data);
	iso(&x1, &y1, z1, data);
	iso(&x2, &y2, z2, data);
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	x1 += data->shift_x;
	x2 += data->shift_x;
	y1 += data->shift_y;
	y2 += data->shift_y;
	i = 0;
    x = x1;
    y = y1;
	step = get_step(delta_x, delta_y);
	x_inc = (float)delta_x / (float)step;
	y_inc = (float)delta_y / (float)step;
	while (i <= step)
	{
		mlx_pixel_put(data->mlx, data->window, (int)x, (int)y, data->color);
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
			if (x < data->width - 1)
				dda_line(x, y, x + 1, y, data);	
			if (y < data->height - 1)
				dda_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}
