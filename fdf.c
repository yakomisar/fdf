#include "fdf.h"

int main(int argc, char **argv)
{
    fdf *data;

    data = (fdf*)malloc(sizeof(fdf));
    read_file(data);
    
    return (0);
}
