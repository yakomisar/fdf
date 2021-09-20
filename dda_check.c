# include <stdlib.h>
# include <stdio.h>
# include <math.h>

void    dda_line(int x1, int y1, int x2, int y2)
{
	int		delta_x;
	int		delta_y;
	float	x_inc;
	float	y_inc;
	int		step;
	int		i;
    float   x;
    float   y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	i = 0;
    x = (float)x1;
    y = (float)y1;
	if (abs(delta_x) > abs(delta_y))
		step = abs(delta_x);
	else
		step = abs(delta_y);
	
	x_inc = (float)delta_x / (float)step;
	y_inc = (float)delta_y / (float)step;
    printf("x_inc = %f\n", x_inc);
    printf("y_inc = %f\n", y_inc);
	while (i <= step)
	{
		printf("x - %d   | y - %d\n", (int)x, (int)y);
		x = x + x_inc;
		y = y + y_inc;
        printf("x - %f\n", x);
        printf("y - %f\n", y);
		i++;
	}
}

int main(void)
{
    dda_line(5,4,12,7);
    return (0);
}