#include "ethernet.h"
#include "ipv4.h"
#include "tcp.h"
#include "http.h"
#include "frame.h"

#ifndef FLOW_GRAPH
#define FLOW_GRAPH

void print_heading_row();
void print_final_row();

void print_comm (char *bytes, int *frame_counter);
void print_flowgraph(frame *ptr, char *filter);
void print_flow(frame *Frame);

char *center_string(const char *str1, const char *str2);

void print_http_fg(tcp *tcp_frame, e_http *http_frame);
void print_ipv4_fg(ipv4 *ipv4_frame);

char *printed_tcp_flags_fg(tcp *tcp_frame);
void cat_info(char *name, char *dst, char *src, int *space_left, int *boolean);
void print_tcp_fg(tcp* tcp_frame);

void fprint_heading_row(FILE *fd);
void fprint_final_row(FILE *fd);
void fprint_flowgraph(FILE *fd, frame *ptr, char *filter);
void fprint_flow(FILE *fd, frame *Frame);
void fprint_ipv4_fg(FILE *fd, ipv4 *ipv4_frame);
void fprint_tcp_fg(FILE *fd, tcp* tcp_frame);
void fprint_http_fg(FILE *fd, tcp *tcp_frame, e_http *http_frame);

#endif // FLOW_GRAPH