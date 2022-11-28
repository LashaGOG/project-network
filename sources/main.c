#include "./headers/reader.h"
#include "./headers/tests.h"
#include "./headers/tools.h"
#include "./headers/ethernet.h"
int main(void)
{
    // static int frame_count = 0; 
    
    /* TEST DE TOOLS.C */
    // test_hexToBin();
    // test_binToHex(); 
    // test_hexToDec(); 
    // test_decToHex();
    // test_decToBin(); 
    // test_binToDec(); 
    // test_hexToBinchar();
    /* END TEST */

    /* TEST DE READER.C */
    // test_frametostr_verif();
    /* END TEST */

    /* TEST DE ETHERNET.C */
    //test_get_mac_address();

    /* TEST DE IPV4.C */
    test_ipv4();
    return 0;
}