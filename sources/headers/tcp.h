#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "tools.h"

#ifndef TCP
#define TCP
typedef struct _tcp_flags {
    char *val_hexa; // valeur in hexa of flags
    char *reserved; //6
    int urg; // 1 bit
    int ack; // 1 bit
    int psh; // 1 bit
    int rst; // 1 bit
    int syn; // 1 bit
    int fin; // 1 bit
}tcp_flags; // 12 bits

typedef struct _tcp { // !!! Options + padding not treated in this structure !!!
    int num_frame ;     // relative ACK AND SEQ numbers are not treated !!! 
    char *src_port ; // 2 bytes
    char *dst_port ; // 2 bytes 
    char *seq_number; // sequence number : 4 bytes
    char *ack_number; // acknowledgment number : 4 bytes
    char *thl; // 4 bits
    tcp_flags *flags; // reserved + flags = 12 bits
    char *window; // 2 bytes
    char *checksum; // 2 bytes
    char *urg_pointer; // 2 bytes
    char *Payload;
}tcp; // 20 bytes

char *get_port(char *bytes); 
void get_src_dest_port_raw (char *bytes, char **src_port, char **dst_port);
char *get_seq_number_raw(char *bytes); 
char *get_ack_number_raw(char *bytes); 
char *get_thl(char *bytes); 
tcp_flags *get_tcp_flags(char *bytes); 
char *get_window(char *bytes); 
char *get_checksum(char *bytes); 
char *get_urg_pointer(char *bytes); 

tcp *create_tcp (char *bytes, int num); 
tcp_flags *create_tcp_flags(char *reserved, char *val_hx, int urg, int ack, int psh, int rst, int syn, int fin); 
void delete_tcp_flags (tcp_flags *tflags); 
void delete_tcp (tcp *tcp_seg); 

void print_tcp_flags (tcp_flags *tflags);
void print_tcp (tcp *tcp_seg,int print_details);

#endif // TCP