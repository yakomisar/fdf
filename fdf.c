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

int main(int argc, char **argv)
{
    fdf *data;

    (void)argc;

    printf("Trying malloc space for data:\n");
    data = (fdf*)malloc(sizeof(fdf));
    if (!data)
    {
        printf("Error!!");
    }
    printf("Go to read function:\n");
    read_file(argv[1], data);
    
    int i;
    int j;

    i = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            printf("%3d ", data->z_matrix[i][j]);
            j++;
        }
        i++;
        printf("\n");
    }
	// if (data)
		//dynamic_array_free(data, 11);
    return (0);
}
