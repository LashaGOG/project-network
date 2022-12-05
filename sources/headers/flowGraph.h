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

char *center_string(const char *str1, const char *str2);
void print_http_fg(tcp *tcp_frame, e_http *http_frame);
void print_ipv4_fg(ipv4 *ipv4_frame);

#endif // FLOW_GRAPH