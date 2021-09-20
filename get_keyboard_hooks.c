#include <stdio.h>
#include <stdlib.h>
#include "minilibx_macos/mlx.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

// int	key_hook(int keycode, t_vars *vars)
// {
// 	printf("%d - pressed\n", keycode);

//     return (0);
// }

int	close_window(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		printf("ESC pressed");
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	// mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, close_window, &vars);
	mlx_loop(vars.mlx);

    return (0);
}