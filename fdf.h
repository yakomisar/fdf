#ifndef FDF_H
# define FDF_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "minilibx_macos/mlx.h"

typedef struct s_fdf
{
	int	width;
	int	height;
	int	shift_x;
	int	shift_y;
	int	zoom;
	int	**z_matrix;
	float	angle;

	void	*mlx;
	void	*window;
	
}   fdf;

void	read_file(char *filename, fdf *data);
void    dda_line(int x1, int y1, int x2, int y2, fdf *data);
int		get_next_line(int fd, char **line);
int		ft_atoi(const char *str);
void	draw_map(fdf *data);

#endif