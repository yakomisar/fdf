#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct
{
	int	width;
	int	height;
	int	**z_matrix;

	void	*x_ptr;
	void	*y_ptr;
}   fdf;

#endif