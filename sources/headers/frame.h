#include "ethernet.h"
#include "ipv4.h"
#include "tcp.h"
#include "http.h"
#include "tools.h"
#include "flowGraph.h"
#include "reader.h"

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
    struct _fram *suiv;
} frame;


frame *create_frame(char *bytes, int *num);
frame *queue_frame(frame **ptr, frame *suiv);

void filter(char *filter, frame *list);

void delete_frame(frame *fr);
void delete_linked_frames(frame *fr);

#endif
