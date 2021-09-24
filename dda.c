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

static void	iso(int *x, int *y, int z, float angle)
{
	int		previous_x;
    int		previous_y;
	
	previous_x = *x;
	previous_y = *y;
    *x = (previous_x - previous_y) * cos(angle);
    *y = -z + (previous_x + previous_y) * sin(angle);
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
	x1 *= data->zoom;
	x2 *= data->zoom;
	y1 *= data->zoom;
	y2 *= data->zoom;
	iso(&x1, &y1, z1, data->angle);
	iso(&x2, &y2, z2, data->angle);
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	x1 += data->shift_x;
	x2 += data->shift_x;
	y1 += data->shift_y;
	y2 += data->shift_y;
	i = 0;
    x = x1;
    y = y1;
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
			if (x < data->width - 1)
				dda_line(x, y, x + 1, y, data);	
			if (y < data->height - 1)
				dda_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}
