#include "./headers/reader.h"
#include "./headers/tests.h"
#include "./headers/tools.h"
#include "./headers/ethernet.h"
#include "./headers/tcp.h"

#include "./headers/flowGraph.h"
#include "./headers/http.h"

int main(void)
{
    // static int frame_count = 0; 
    
    /* TEST DE TOOLS.C */
    // test_hexToBin();
    // test_binToHex(); 
    // test_hexToDec(); 
    // test_hexToDec_c();
    // test_decToHex();
    // test_decToBin(); 
    // test_binToDec(); 
    // test_hexToBinchar();
    //test_hexToChar();
    //test_hex_to_ip();
    /* END TEST */

    /* TEST DE READER.C */
    // test_frametostr_verif();
    /* END TEST */

    /* TEST DE ETHERNET.C */
    //test_get_mac_address();

    /* TEST DE IPV4.C */
    // test_ipv4();

    /* TEST DE TCP.C */
    // test_tcp();
    
    /* TEST DE HTTP.C */
    //test_http();
    //test_get_http();

    /* TEST DE FLOWGRAPH.C */
    test_flow_graph();

    return 0;
}