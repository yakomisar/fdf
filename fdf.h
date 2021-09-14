#ifndef FDF_H
# define FDF_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct
{
	int	width;
	int	height;
	int	z_line;
	int	**z_matrix;

	void	*x_ptr;
	void	*y_ptr;
}   fdf;

void	read_file(char *filename, fdf *data);
int		get_next_line(int fd, char **line);

#endif