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

int	close_window(int keycode, fdf *data)
{
	if (keycode == 53)
	{
		printf("ESC pressed");
		mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
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
    printf("Go to read function:\n");
    read_file(argv[1], data);

	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, 1000, 1000, argv[1]);
	draw_map(data);
	mlx_hook(data->window, 2, 1L<<0, close_window, data);
	mlx_loop(data->mlx);
	// if (data)
		//dynamic_array_free(data, 11);
    return (0);
}
