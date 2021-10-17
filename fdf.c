/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:37:59 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/15 19:36:43 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void    dynamic_array_free(fdf *data)
{
    int i;

    i = 0;
    while (i < data->height)
    {
        free(data->z_matrix[i]);
        i++;
    }
	free(data->z_matrix);
	mlx_destroy_image(data->mlx, data->window);
	if (data)
		free(data);
}

void	shift_window(int key, fdf *data)
{
	if (key == 126)
		data->shift_y -= 10;
	if (key == 125)
		data->shift_y += 10;
	if (key == 124)
		data->shift_x += 10;
	if (key == 123)
		data->shift_x -= 10;
	mlx_clear_window(data->mlx, data->window);
	draw_map(data);
}

void	zoom_window(int key, fdf *data)
{
	if (key == 27 && data->zoom != 5)
	{
		data->zoom -= 2;
	}
	if (key == 24)
		data->zoom += 2;
	mlx_clear_window(data->mlx, data->window);
	draw_map(data);
}

void	rotate_window(int key, fdf *data)
{
	float	pi;

	pi = M_PI;
	if (key == 18)
	{
		data->my_angle.first -= pi / 12;
		data->my_angle.second += pi / 12;
		data->my_angle.third = 0;
	}
	if (key == 19)
	{
		data->my_angle.first += pi / 12;
		data->my_angle.second -= pi / 12;
		//data->third += 0.1;
	}
	mlx_clear_window(data->mlx, data->window);
	draw_map(data);
}

void	change_projection(int key, fdf *data)
{
	float	pi;

	pi = M_PI;
	if (key == 20)
	{
		data->my_angle.first = 0;
		data->my_angle.second = pi/2;
		data->my_angle.third = 0;
	}
	if (key == 21)
	{
		data->my_angle.first = 0;
		data->my_angle.second = 0;
		data->my_angle.third = pi/2;
	}
	if (key == 23)
	{
		data->my_angle.first = pi / 6;
		data->my_angle.second = (5 * pi) / 6;
		data->my_angle.third = pi / 2;
	}
	mlx_clear_window(data->mlx, data->window);
	draw_map(data);
}

int	window_action(int keycode, fdf *data)
{
	if (keycode == 18 || keycode == 19)
		rotate_window(keycode, data);
	if (keycode == 20 || keycode == 21 || keycode == 23)
		change_projection(keycode, data);
	if (keycode == 27 || keycode == 24)
		zoom_window(keycode, data);
	if (keycode == 53)
	{
		dynamic_array_free(data);
		exit(0);
	}
	if (keycode == 126 || keycode == 125 || keycode == 124 || keycode == 123)
		shift_window(keycode, data);
	return (0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	data_init(fdf *data, char *filename)
{
	float	pi;

	pi = M_PI;
	data->shift_x = 100;
	data->shift_y = 100;
	data->zoom = 5;
	data->my_angle.first = pi / 6;
	data->my_angle.second = (5 * pi) / 6;
	data->my_angle.third = pi / 2;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, 1500, 1500, filename);
	data->x1 = 0;
	data->x2 = 0;
	data->y1 = 0;
	data->y2 = 0;
}

int	main(int argc, char **argv)
{
	int	check;
    fdf	*data;

	if (argc != 2)
	{
		ft_putstr("ERROR: Incorrect number of arguments.\n");
		ft_putstr("HINT: Please use the following format: ");
		ft_putstr("./[Program name] [path of the map]");
		return (1);
	}
	check = open(argv[1], O_RDONLY);
	if (check == -1)
	{
		ft_putstr("Unable to open file.\n");
		return (1);
	}
    data = (fdf*)malloc(sizeof(fdf));
	read_file(argv[1], data);
	data_init(data, argv[1]);
	draw_map(data);
	mlx_hook(data->window, 2, 1L<<0, window_action, data);
	mlx_loop(data->mlx);
	return (0);
}
