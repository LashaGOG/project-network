#include "tools.h"
#include "reader.h"
#include "ethernet.h"
#include "ipv4.h"
#include "tcp.h"
#include "flowGraph.h"
#include "http.h"
#include "frame.h"

#ifndef TESTS
#define TESTS

/* TESTS DE TOOLS.C */
void test_hexToBin();
void test_binToHex();
void test_hexToDec();
void test_hexToDec_c ();
void test_decToHex ();
void test_decToBin();
void test_binToDec();
void test_hexToBinchar();
void test_hexToChar();
void test_hex_to_ip();

/* TESTS DE READER.C */
void test_frametostr_verif();

/* TESTS DE ETHERNET.C*/
void test_get_mac_address();

/* TESTS DE IPV4.C */
void test_ipv4();

/* TESTS DE TCP.C */
void test_tcp(); 

/* TEST DE FLOW GRAPH */
void test_flow_graph();

/* TESTS DE HTTP.C */
void test_http();
void test_get_http();

/* TESTS DE FRAME.C */
void test_frame();

#endif