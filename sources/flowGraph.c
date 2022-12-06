#include "./headers/flowGraph.h"
#define MAX 80


void print_heading_row() {
    printf("+------+-----------------+-----------------------------------+-----------------+\n");
    printf("|  N   |    IP SOURCE    |                                   | IP  DESTINATION |\n");
    printf("+------+-----------------+-----------------------------------+-----------------+\n");
}

void print_comm (char *bytes, int *frame_counter) 
{
    eth_frame *eFrame = create_eth_frame(bytes,frame_counter);
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
    ipv4 *ipv4_frame = create_ipv4(eFrame->Payload,frame_counter); 
    
    printf("|      |                  TCP et Trucs ICI                                      |\n");
    printf("| %d | %s      ---------------------------------->     %s |\n",eFrame ->num_frame, ipv4_frame->src_ip, ipv4_frame->dest_ip);
    printf("|      |                  des trucs en plus?                                    |\n");
    
    printf("+------------------------------------------------------------------------------+\n");

    delete_ipv4(ipv4_frame);
    delete_eth_frame(eFrame);
}

// void *print_flow(eth_frame *eFrame){
//    if (eFrame->Payload != NULL){
//        ipv4 *ip_frame = create_ipv4(eFrame->Payload);
//        if (ip_frame->Payload != NULL){
//            tcp *tcp_frame = create_tcp(ip_frame->Payload);
//            if (tcp_frame->Payload != NULL){
//                http *http_frame =  create_http(tcp_frame->Payload);
//                print_http_fg(tcp_frame, http_frame);
//                delete_http(http_frame);
//            }
//            else{
//                print_tcp_fg(tcp_frame);
//            }
//            delete_tcp(tcp_frame);
//        }
//        print_ip_fg(ip_frame);
//        printf("|      |                                                                       |\n");
//        delete_ipv4(ipv4_frame);
//    }
// }

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
    
    char *http_header = center_string("                                   ", entete);
    free(entete);

    printf("|      |%s%s%s|\n", port_src, http_header, port_dest);
    free(http_header);
    free(port_dest);
    free(port_src);
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

void cat_info(char *name, char *dst, char *src, int *space_left, int *bool) {
    /**/
    if (*(space_left) < 1) return ; 
    int length_src = (int)strlen(src), length_name = (int)strlen(name);
    
    if (*(space_left) > length_name) {
        strcat(dst,name);
        *(space_left) -= length_name;
    } else {
        strncat(dst,name,*(space_left));
        strcat(dst,"...");
        *bool = 0; 
        return;
    }

    if (*(space_left) > length_src) {
        strcat(dst,src);
        *(space_left) -= length_src;
        return;
    } else {
        strncat(dst,src,*(space_left));
        strcat(dst,"...");
        *bool = 0;
        return;
    }
}
void print_tcp_fg(tcp* tcp_frame) {

    char *flow_info = (char *) calloc (36, sizeof(char));

    /* printing ports */
    char *port = hexToDec_c(tcp_frame->src_port);
    char *port_src = center_string("                 ", port);
    free(port);

    port = hexToDec_c(tcp_frame->dst_port);
    char *port_dest = center_string("                 ", port);
    free(port);

    
    char *flags = printed_tcp_flags_fg(tcp_frame);
    char *seq = unsLongToStr(hexToUnsLong(tcp_frame->seq_number));
    char *ack = unsLongToStr(hexToUnsLong(tcp_frame->ack_number));
    char *window = unsLongToStr(hexToUnsLong(tcp_frame->window));

    /* getting flow info */
    
    int space_left = 32 ;
    int bool = 1; 
    if (bool == 1) cat_info("",flow_info,flags,&space_left,&bool);
    if (bool == 1) cat_info(" win=",flow_info,window,&space_left,&bool);
    if (bool == 1) cat_info(" seq=",flow_info,seq,&space_left,&bool);
    if (bool == 1) cat_info(" ack=",flow_info,ack,&space_left,&bool);

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