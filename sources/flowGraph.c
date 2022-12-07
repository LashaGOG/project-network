#include "./headers/flowGraph.h"
#define MAX 80

void print_flowgraph(frame *ptr)
{
    print_heading_row();
    frame *tmp = ptr;
    while (tmp)
    {
        if (tmp->print == 1)
        {
            print_flow(tmp);
        }
        tmp = tmp->suiv;
    }
    print_final_row();
}

void print_heading_row() {
    printf("+------+-----------------+-----------------------------------+-----------------+\n");
    printf("|  N   |    IP SOURCE    |                                   | IP  DESTINATION |\n");
    printf("+------+-----------------+-----------------------------------+-----------------+\n");
}
void print_final_row()
{
    printf("+------+-----------------+-----------------------------------+-----------------+\n");
}

void fprint_heading_row(FILE *fd) {
    fprintf(fd, "+------+-----------------+-----------------------------------+-----------------+\n");
    fprintf(fd, "|  N   |    IP SOURCE    |                                   | IP  DESTINATION |\n");
    fprintf(fd, "+------+-----------------+-----------------------------------+-----------------+\n");
}
void fprint_final_row(FILE *fd)
{
    fprintf(fd, "+------+-----------------+-----------------------------------+-----------------+\n");
}

void print_comm (char *bytes, int *frame_counter) 
{
    eth_frame *eFrame = create_eth_frame(bytes, *frame_counter);
    if (!eFrame) {
        printf("Error allocating memory\n");
        return; 
    }
    // print_eth_frame(eFrame);
    if (strcmp(eFrame->proto,"0800") == 1) 
    {
        printf ("Invalid input, Type != IPV4\n");
        delete_eth_frame(eFrame);
        return; 
    } 
    eFrame->num_frame = 1000;
    ipv4 *ipv4_frame = create_ipv4(eFrame->Payload, *frame_counter); 
    
    // printf("|      |                  TCP et Trucs ICI                                      |\n");
    // printf("| %d | %s      ---------------------------------->     %s |\n",eFrame ->num_frame, ipv4_frame->src_ip, ipv4_frame->dest_ip);
    // printf("|      |                  des trucs en plus?                                    |\n");
    
    // printf("+------------------------------------------------------------------------------+\n");

    delete_ipv4(ipv4_frame);
    delete_eth_frame(eFrame);
}

void print_flow(frame *Frame)
{
    if (Frame->eth != NULL)
    {
        if (Frame->ip != NULL)
        {
            if (Frame->tcp_ != NULL)
            {
                if (Frame->http != NULL)
                {
                    print_http_fg(Frame->tcp_, Frame->http);
                }
                else
                {
                    print_tcp_fg(Frame->tcp_);
                }
            }
            print_ipv4_fg(Frame->ip);
            puts("|      |                                                                       |");
        }
    }
    return;
}


//    if (eFrame->Payload != NULL){
//        ipv4 *ip_frame = create_ipv4(eFrame->Payload,eFrame->num_frame);
//        if (ip_frame->Payload != NULL){
//            tcp *tcp_frame = create_tcp(ip_frame->Payload,eFrame->num_frame);
//            if (tcp_frame != NULL)
//            {
//                 if (tcp_frame->Payload != NULL)
//                 {
//                     e_http *http_frame = get_http(tcp_frame->Payload);
//                     if (http_frame != NULL)
//                     {
//                         print_http_fg(tcp_frame, http_frame);
//                         delete_http(http_frame);
//                     }
//                     else
//                         tc = 1; 
//                 }
//                 if (tc == 1){
//                     print_tcp_fg(tcp_frame);
//                     delete_tcp(tcp_frame);
//                 }
//             }
//             print_ipv4_fg(ip_frame);
//             printf("+------+-----------------------------------------------------------------------+\n");
//             delete_ipv4(ip_frame);
//         }
//     }
//     return;

char *center_string(const char *str1, const char *str2) {
    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);

    if (str2_len > str1_len)
        return strdup(str2);
    
    size_t leading_spaces = 0;
    size_t trailing_spaces = 0;

    for (size_t i = 0; i < str2_len; i++) {
        if (str2[i] == ' ') {
            if (i < str2_len - 1) {
                trailing_spaces++;
            }
        } else {
            break;
        }
    }

    size_t start_index = (str1_len - (str2_len - leading_spaces - trailing_spaces)) / 2;
    size_t end_index = start_index + (str2_len - leading_spaces - trailing_spaces);

    char *result = (char *)malloc(str1_len + 1);
    if (result == NULL) 
        return NULL;
    
    strncpy(result, str1, start_index);
    strncpy(&result[start_index], &str2[leading_spaces], str2_len - leading_spaces - trailing_spaces);
    strncpy(&result[end_index], &str1[end_index], str1_len - end_index);
    
    result[str1_len] = '\0';
    return result;
}

void print_http_fg(tcp *tcp_frame, e_http *http_frame)
{
    char *port = hexToDec_c(tcp_frame->src_port);
    char *port_src = center_string("                 ", port);
    free(port);

    port = hexToDec_c(tcp_frame->dst_port);
    char *port_dest = center_string("                 ", port);
    free(port);

    int len = strlen(http_frame->http_header->meth_ver) + strlen(http_frame->http_header->uri_stat) + strlen(http_frame->http_header->ver_msg) + 1;
    char *entete = (char *)  calloc(len, sizeof(char));
    
    char *temp = hexToChar(http_frame->http_header->meth_ver);
    strcat(entete, temp);
    free(temp);
    
    temp = hexToChar(http_frame->http_header->uri_stat);
    strcat(entete, temp);
    free(temp);

    temp = hexToChar(http_frame->http_header->ver_msg);
    strcat(entete, temp);
    free(temp);
    
    char *http_header = center_string("                                     ", entete);
    free(entete);

    printf("|      |%s%s%s|\n", port_src, http_header, port_dest);
    free(http_header);
    free(port_dest);
    free(port_src);
}

void print_ipv4_fg(ipv4 *ipv4_frame)
{
    char *ip = hex_to_ip(ipv4_frame->src_ip);
    char *src_ip = center_string("                 ", ip);
    free(ip);

    ip = hex_to_ip(ipv4_frame->dest_ip);
    char *dest_ip = center_string("                 ", ip);
    free(ip);

    char N[5] = {0};
    sprintf(&(N[0]), "%d", ipv4_frame->num_frame);
    char *number = center_string("      ", N);

    char *arrow = "------------------------------------>";

    printf("|%s|%s%s%s|\n", number, src_ip, arrow, dest_ip);
    printf("|      |                                                                       |\n");
    free(src_ip);
    free(dest_ip);
    free(number);
}

char *printed_tcp_flags_fg(tcp *tcp_frame) {
    /* return formatted set flags ex : [ACK] if ack is set */
    int urg, ack, psh, rst, syn, fin ; 
    tcp_flags *tflags = tcp_frame->flags;
    
    urg = tflags->urg;
    ack = tflags->ack; 
    psh = tflags->psh;
    rst = tflags->rst; 
    syn = tflags->syn;
    fin = tflags->fin;

    char *printed_flags = (char *)calloc(30,sizeof(char));

    if (urg == 1) {
        strcat(printed_flags,"[URG]");
    }
    if (ack == 1) {
        strcat(printed_flags,"[ACK]");
    }
    if (psh == 1) {
        strcat(printed_flags,"[PSH]");
    }
    if (rst == 1) {
        strcat(printed_flags,"[RST]");
    }
    if (syn == 1) {
        strcat(printed_flags,"[SYN]");
    }
    if (fin == 1) {
        strcat(printed_flags,"[FIN]");
    }
    return printed_flags;
}

void cat_info(char *name, char *dst, char *src, int *space_left, int *boolean) {
    /**/
    if (*(space_left) < 1) return ; 
    int length_src = (int)strlen(src), length_name = (int)strlen(name);
    
    if (*(space_left) > length_name) {
        strcat(dst,name);
        *(space_left) -= length_name;
    } else {
        strncat(dst,name,*(space_left));
        strcat(dst,"...");
        *boolean = 0; 
        return;
    }

    if (*(space_left) > length_src) {
        strcat(dst,src);
        *(space_left) -= length_src;
        return;
    } else {
        strncat(dst,src,*(space_left));
        strcat(dst,"...");
        *boolean = 0;
        return;
    }
}

void print_tcp_fg(tcp* tcp_frame) {

    char *flow_info = (char *) calloc (36, sizeof(char));

    /* printing ports */
    char *port = hexToDec_c(tcp_frame->src_port);
    char *port_src = center_string("                  ", port);
    free(port);

    port = hexToDec_c(tcp_frame->dst_port);
    char *port_dest = center_string("                  ", port);
    free(port);

    
    char *flags = printed_tcp_flags_fg(tcp_frame);
    char *seq = unsLongToStr(hexToUnsLong(tcp_frame->seq_number));
    char *ack = unsLongToStr(hexToUnsLong(tcp_frame->ack_number));
    char *window = unsLongToStr(hexToUnsLong(tcp_frame->window));

    /* getting flow info */
    
    int space_left = 32 ;
    int boolean = 1; 
    if (boolean == 1) cat_info("",flow_info,flags,&space_left,&boolean);
    if (boolean == 1) cat_info(" win=",flow_info,window,&space_left,&boolean);
    if (boolean == 1) cat_info(" seq=",flow_info,seq,&space_left,&boolean);
    if (boolean == 1) cat_info(" ack=",flow_info,ack,&space_left,&boolean);

    free(flags);
    free(seq);
    free(ack);
    free(window);

    char *centered_flow_info = center_string("                                   ",flow_info);
    free(flow_info);
    
    printf("|      |%s%s%s|\n", port_src, centered_flow_info, port_dest);

    free(port_dest);
    free(port_src);
    free(centered_flow_info);
}

// void fprint_flow(FILE *fd, eth_frame *eFrame){
//     int tc = 0;

//    if (eFrame->Payload != NULL){
//        ipv4 *ip_frame = create_ipv4(eFrame->Payload,eFrame->num_frame);
//        if (ip_frame->Payload != NULL){
//            tcp *tcp_frame = create_tcp(ip_frame->Payload,eFrame->num_frame);
//            if (tcp_frame != NULL)
//            {
//                 if (tcp_frame->Payload != NULL)
//                 {
//                     e_http *http_frame = get_http(tcp_frame->Payload);
//                     if (http_frame != NULL)
//                     {
//                         fprint_http_fg(fd, tcp_frame, http_frame);
//                         delete_http(http_frame);
//                     }
//                     else
//                         tc = 1; 
//                 }
//                 if (tc == 1){
//                     fprint_tcp_fg(fd, tcp_frame);
//                     delete_tcp(tcp_frame);
//                 }
//             }
//             fprint_ipv4_fg(fd, ip_frame);
//             fprintf(fd, "+------+-----------------------------------------------------------------------+\n");
//             delete_ipv4(ip_frame);
//         }
//     }
//     return;
// }

void fprint_flow(FILE *fd, frame *Frame)
{
    if (Frame->eth != NULL)
    {
        if (Frame->ip != NULL)
        {
            if (Frame->tcp_ != NULL)
            {
                if (Frame->http != NULL)
                {
                    fprint_http_fg(fd, Frame->tcp_, Frame->http);
                }
                else
                {
                    fprint_tcp_fg(fd, Frame->tcp_);
                }
            }
            fprint_ipv4_fg(fd, Frame->ip);
            fputs("|      |                                                                       |", fd);
        }
    }
    return;
}

void fprint_http_fg(FILE *fd, tcp *tcp_frame, e_http *http_frame)
{
    char *port = hexToDec_c(tcp_frame->src_port);
    char *port_src = center_string("                 ", port);
    free(port);

    port = hexToDec_c(tcp_frame->dst_port);
    char *port_dest = center_string("                 ", port);
    free(port);

    int len = strlen(http_frame->http_header->meth_ver) + strlen(http_frame->http_header->uri_stat) + strlen(http_frame->http_header->ver_msg) + 1;
    char *entete = (char *)  calloc(len, sizeof(char));
    
    char *temp = hexToChar(http_frame->http_header->meth_ver);
    strcat(entete, temp);
    free(temp);
    
    temp = hexToChar(http_frame->http_header->uri_stat);
    strcat(entete, temp);
    free(temp);

    temp = hexToChar(http_frame->http_header->ver_msg);
    strcat(entete, temp);
    free(temp);
    
    char *http_header = center_string("                                     ", entete);
    free(entete);

    fprintf(fd, "|      |%s%s%s|\n", port_src, http_header, port_dest);
    free(http_header);
    free(port_dest);
    free(port_src);
}

void fprint_ipv4_fg(FILE *fd, ipv4 *ipv4_frame)
{
    char *ip = hex_to_ip(ipv4_frame->src_ip);
    char *src_ip = center_string("                 ", ip);
    free(ip);

    ip = hex_to_ip(ipv4_frame->dest_ip);
    char *dest_ip = center_string("                 ", ip);
    free(ip);

    char N[5] = {0};
    sprintf(&(N[0]), "%d", ipv4_frame->num_frame);
    char *number = center_string("      ", N);

    char *arrow = "------------------------------------>";

    fprintf(fd, "|%s|%s%s%s|\n", number, src_ip, arrow, dest_ip);
    fprintf(fd, "|      |                                                                       |\n");
    free(src_ip);
    free(dest_ip);
    free(number);
}

void fprint_tcp_fg(FILE *fd, tcp* tcp_frame) {

    char *flow_info = (char *) calloc (36, sizeof(char));

    /* printing ports */
    char *port = hexToDec_c(tcp_frame->src_port);
    char *port_src = center_string("                  ", port);
    free(port);

    port = hexToDec_c(tcp_frame->dst_port);
    char *port_dest = center_string("                  ", port);
    free(port);

    
    char *flags = printed_tcp_flags_fg(tcp_frame);
    char *seq = unsLongToStr(hexToUnsLong(tcp_frame->seq_number));
    char *ack = unsLongToStr(hexToUnsLong(tcp_frame->ack_number));
    char *window = unsLongToStr(hexToUnsLong(tcp_frame->window));

    /* getting flow info */
    
    int space_left = 32 ;
    int boolean = 1; 
    if (boolean == 1) cat_info("",flow_info,flags,&space_left,&boolean);
    if (boolean == 1) cat_info(" win=",flow_info,window,&space_left,&boolean);
    if (boolean == 1) cat_info(" seq=",flow_info,seq,&space_left,&boolean);
    if (boolean == 1) cat_info(" ack=",flow_info,ack,&space_left,&boolean);

    free(flags);
    free(seq);
    free(ack);
    free(window);

    char *centered_flow_info = center_string("                                   ",flow_info);
    free(flow_info);
    
    fprintf(fd, "|      |%s%s%s|\n", port_src, centered_flow_info, port_dest);

    free(port_dest);
    free(port_src);
    free(centered_flow_info);
}