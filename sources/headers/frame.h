#include "ethernet.h"
#include "ipv4.h"
#include "tcp.h"
#include "http.h"
#include "tools.h"
#include "flowGraph.h"
#include "reader.h"
#include <wchar.h>
#include <regex.h>
#include <stdbool.h>

#ifndef _FRAME
#define _FRAME

typedef struct _frame
{
    int num_frame;
    char *bytes;
    eth_frame *eth;
    ipv4 *ip;
    tcp *tcp_;
    e_http *http;
    int print;
    struct _frame *suiv;
} frame;


frame *create_frame(char *bytes, int *num);
frame *queue_frame(frame **ptr, frame *suiv);
void print_frame(frame *ptr);
void print_specific_frame(frame *fr, int frame_number);

char *filter(frame *list);
char *verif_input(char *prompt);
void filter_protocol(char *str, frame *ptr);
void filter_mac(char *str, frame *ptr);
void filter_ip(char *str, frame *ptr);
void filter_port(char *str, frame *ptr);

void delete_frame(frame *fr);
void delete_linked_frames(frame *fr);

#endif
