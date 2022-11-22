#include "./headers/reader.h"
#include "./headers/tests.h"
#include "./headers/tools.h"
int main(void)
{
    FILE *fd = fopen("test2.txt", "w");
    fclose(fd);
    fd = fopen("test3.txt", "w");
    fclose(fd);
    frametostr("format.txt", "test2.txt");
    verif("test2.txt", "test3.txt");

    /* TEST DE TOOLS.C */
    test_hexToBin();
    test_binToHex(); 
    test_hexToDec(); 
    /* END TEST */
    return 0;
}