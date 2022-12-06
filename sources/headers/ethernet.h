#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

#ifndef ETHERNET_H
#define ETHERNET_H

typedef struct _eth_frame{ // !!! Payload and CRC are not TREATED in this structure !!!
    int num_frame; 
    char *src_mac;  // source mac adress (ex: AA:BB:CC:DD:FF:EE)
    char *dest_mac;  // destination mac address 
    char *proto;    // protocole 
    char *Payload;
}eth_frame;

char *get_mac_address(char *bytes);
void get_mac_dest_src (char *bytes, char **mac_src, char **mac_dst);
char* get_eth_proto (char *bytes);

eth_frame *create_eth_frame (char *bytes, int num);
void print_eth_frame (eth_frame *ef); 
void delete_eth_frame (eth_frame *ef);

#endif //ETHERNET_H