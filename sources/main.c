#include "./headers/reader.h"

int main(void)
{
    FILE *fd = fopen("test2.txt", "w");
    fclose(fd);
    frametostr("format.txt", "test2.txt");
    verif("test2.txt", "test3.txt");
    return 0;
}