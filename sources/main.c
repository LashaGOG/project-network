#include "./headers/reader.h"
#include "./headers/tests.h"
#include "./headers/tools.h"
int main(void)
{
    /* TEST DE TOOLS.C */
    test_hexToBin();
    test_binToHex(); 
    test_hexToDec(); 
    /* END TEST */

    /* TEST DE READER.C */
    test_frametostr_verif();
    /* END TEST */
    return 0;
}