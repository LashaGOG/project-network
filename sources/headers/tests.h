#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "tools.h"
#include "reader.h"
#include "ethernet.h"
#include "ipv4.h"
#include "tcp.h"
#include "http.h"

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

/* TESTS DE READER.C */
void test_frametostr_verif();

/* TESTS DE ETHERNET.C*/
void test_get_mac_address();

/* TESTS DE IPV4.C */
void test_ipv4();

/* TESTS DE TCP.C */
void test_tcp(); 

/* TESTS DE HTTP.C */
void test_http();

#endif