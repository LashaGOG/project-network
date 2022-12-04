#include "tools.h"
#include "reader.h"

#ifndef IPV4_H
#define IPV4_H

typedef struct _ipv4{
    int num_frame;  
    char *version;  //4 bits
    char *header_length;     //4 bits
    struct _tos *typesos;    //1 byte
    char *total_length;  //2 bytes
    char *identifier;    //2 bytes
    struct _fragmentation *fragment;    //2 bytes (with 3 bits for R, DF and MF)
    char *ttl;   //1 byte
    char *protocol;     //1 byte
    char *header_checksum;  //2 bytes
    char *src_ip;   //4 bytes
    char *dest_ip;  //4 bytes
    char *Payload;
}ipv4;  //20 bytes

typedef struct _fragmentation{
    int R;
    int DF;
    int MF;
    char *offset;
}fragmentation;

typedef struct _tos{
    char *precedence;
    int delay;
    int throughput;
    int reliability;
    int cost;
    int reserved;
}tos;

char *get_ip_version (char *bytes);
char *get_header_length (char *bytes);
tos *get_TOS (char *bytes);
char *get_total_length (char *bytes);
char *get_identifier (char *bytes);
fragmentation *get_fragmentation (char *bytes);
char *get_ttl (char *bytes);
char *get_protocol (char *bytes);
char *get_header_checksum (char *bytes);
char *get_ip (char *bytes);
void get_src_dest_ip (char *bytes, char **ip_src, char **ip_dest);

ipv4 *create_ipv4 (char *bytes, int *num);
fragmentation *create_fragmentation (int R, int DF, int MF, char *offset);
tos *create_tos (char *precedence, int delay, int throughput, int reliability, int cost, int reserved);
void delete_ipv4 (ipv4 *ip);
void delete_fragmentation (fragmentation *fragment);
void delete_tos (tos *typesos);

void print_ipv4(ipv4 *ipf);

#endif //IPV4_H