/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:38:09 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/15 19:55:52 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "minilibx_macos/mlx.h"

typedef struct s_angle
{
	float	first;
	float	second;
	float	third;
}   angle;

typedef struct s_fdf
{
	int	width;
	int	height;
	int	shift_x;
	int	shift_y;
	int	zoom;
	int	**z_matrix;
	int	color;
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	z1;
	int	z2;
	angle	my_angle;

	void	*mlx;
	void	*window;
	
}   fdf;

void	read_file(char *filename, fdf *data);
void	dda_line(fdf *data);
void	get_color(fdf *data);
int		get_next_line(int fd, char **line);
int		ft_atoi(const char *str);
int		get_step(int delta_x, int delta_y);
void	draw_map(fdf *data);
void	ft_putstr(char *str);
void	iso_one(fdf *data);
void	iso_sec(fdf *data);
void    dynamic_array_free(fdf *data);

#endif