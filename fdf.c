#include "fdf.h"

int main(int argc, char **argv)
{
    fdf *data;

    if (argc != 2)
    {
        return (1);
    }
    
    data = (fdf*)malloc(sizeof(fdf));
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
    return (0);
}
