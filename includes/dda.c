/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:37:49 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/15 20:37:05 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_line(fdf *data)
{
	int		delta_x;
	int		delta_y;
	float	x_inc;
	float	y_inc;
	int		step;
	int		i;
	float	x;
	float	y;

	delta_x = data->x2 - data->x1;
	delta_y = data->y2 - data->y1;
	data->x1 += data->shift_x;
	data->y1 += data->shift_y;
	i = 0;
	x = data->x1;
	y = data->y1;
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

void	dda_line(fdf *data)
{
	get_color(data);
	iso_one(data);
	iso_sec(data);
	ft_line(data);
}

void	xy_init(fdf *data, int x, int y, char c)
{
	data->x1 = x;
	data->y1 = y;
	if (c == 'x')
	{	
		data->x2 = x + 1;
		data->y2 = y;
	}
	else
	{
		data->x2 = x;
		data->y2 = y + 1;
	}
}

void	draw_map(fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
			{
				xy_init(data, x, y, 'x');
				dda_line(data);
			}
			if (y < data->height - 1)
			{
				xy_init(data, x, y, 'y');
				dda_line(data);
			}
			x++;
		}
		y++;
	}
}
