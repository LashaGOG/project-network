#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "ethernet.h"
#include "ipv4.h"
#include "tcp.h"
#include "http.h"


#ifndef FLOW_GRAPH
#define FLOW_GRAPH

void print_heading_row();
void print_comm (char *bytes, int *frame_counter);
void *print_flow(eth_frame *eFrame);

#endif // FLOW_GRAPH