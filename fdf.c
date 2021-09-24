/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:37:59 by jmacmill          #+#    #+#             */
/*   Updated: 2021/09/24 19:38:01 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void    dynamic_array_free(fdf *data, int n)
// {
//     int i;

//     i = 0;
//     while (i < n)
//     {
//         free(data->z_matrix[i]);
//         i++;
//     }
// 	free(data);
// }

void	close_window(fdf *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
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
	if (key == 27 && data->zoom != 10)
		data->zoom -= 10;
	if (key == 24)
		data->zoom += 10;
	mlx_clear_window(data->mlx, data->window);
	draw_map(data);
}

void	rotate_window(int key, fdf *data)
{
	if (key == 18)
		data->angle -= 0.1;
	if (key == 19)
		data->angle += 0.1;
	mlx_clear_window(data->mlx, data->window);
	draw_map(data);
}

int	window_action(int keycode, fdf *data)
{
	if (keycode == 18 || keycode == 19)
		rotate_window(keycode, data);
	if (keycode == 27 || keycode == 24)
		zoom_window(keycode, data);
	if (keycode == 53)
		close_window(data);
	if (keycode == 126 || keycode == 125 || keycode == 124 || keycode == 123)
		shift_window(keycode, data);
	return (0);
}

int main(int argc, char **argv)
{
    fdf *data;

	if (argc != 2)
	{
		printf("ERROR: Incorrect number of arguments..\n");
		printf("HINT: Please use the following format: ");
		printf("./[Program name] [path of the map]");
		return (1);
	}
    data = (fdf*)malloc(sizeof(fdf));
    if (!data)
    {
        printf("Error!!");
    }
    read_file(argv[1], data);
	data->shift_x = 10;
	data->shift_y = 10;
	data->zoom = 10;
	data->angle = 0.523599;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, 1000, 1000, argv[1]);
	draw_map(data);
	mlx_hook(data->window, 2, 1L<<0, window_action, data);
	mlx_loop(data->mlx);
	// if (data)
		//dynamic_array_free(data, 11);
    return (0);
}
