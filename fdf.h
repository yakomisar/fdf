#ifndef FDF_H
# define FDF_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_fdf
{
	int	width;
	int	height;
	int	z_line;
	int	**z_matrix;
	
}   fdf;

void	read_file(char *filename, fdf *data);
int		get_next_line(int fd, char **line);
int		ft_atoi(const char *str);

#endif