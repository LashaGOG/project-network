#include "tools.h"

#ifndef IPV4_H
#define IPV4_H

typedef struct _ipv4{
    int num_frame;
    char *version;
    char header_length;
    struct _tos typesos;
    char total_length;
    char identifier;
    struct _fragmentation *fragment;
    char ttl;
    char *protocol;
    char *header_checksum;
    char *src_ip;
    char *dest_ip;
}ipv4;

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
void get_src_dest_ip (char *bytes);

ipv4 *create_ipv4 (char *bytes, int *num);
fragmentation *create_fragmentation (int R, int DF, int MF, char *offset);
tos *create_tos (char* precedence, int delay, int throughput, int reliability, int cost, int reserved);
void delete_fragmentation (fragmentation fragment);
void delete_ipv4 (ipv4 ip);


#endif //IPV4_H