#include "../headers/cub3d.h"

char *f1(int fd)
{
    return(gnl(fd));
}
char *f2(int fd)
{
    return(gnl(fd));
}
int main()
{
    int fd = open("./test.c", O_RDONLY);
    printf("f1 = %s\n", f1(fd));
    printf("f2 = %s\n", f2(fd));
}