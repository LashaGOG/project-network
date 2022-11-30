#include "./headers/tcp.h"

char *get_port(char *bytes) {
    char *ch1 = strndup(&bytes[0],2); // copy 2 bites
    char *ch2 = strndup(&bytes[3],2); // copy 2 bites

    int length = strlen(ch1) + strlen(ch2);  

    char *port = (char *) malloc ((length + 1) * sizeof(char)); 
    
    strcpy(port,ch1);
    strcat(port,ch2);

    free(ch1);
    free(ch2);

    return port ; 
}

void get_src_dest_port_raw (char *bytes, char **src_port, char **dst_port) {
    /* return source and destination ports for TCP segment */
    *(src_port) = get_port(&bytes[0]);
    *(dst_port) = get_port(&bytes[6]);
}

char *get_seq_number_raw(char *bytes) {
    /* return raw sequence number value in hexadecimal */
    char *seq_number_untrimmed = strndup(&bytes[12],11); // copy 4 bytes of sequence number
    int length = strlen(seq_number_untrimmed) + 1; 
    char *seq_number_raw = (char *) malloc (length * sizeof(char)); 
    remove_spaces(seq_number_raw,seq_number_untrimmed);
    free(seq_number_untrimmed);
    return seq_number_raw;
}

char *get_ack_number_raw(char *bytes) {
    /* return raw acknowledgment number in hexadecimal */
    char *ack_untrimmed = strndup(&bytes[24],11); // copy 4 bytes
    int length = strlen(ack_untrimmed) + 1; 
    char *ack_raw = (char *) malloc (length * sizeof(char)); 
    remove_spaces(ack_raw,ack_untrimmed);
    free(ack_untrimmed);
    return ack_raw;
}

char *get_thl(char *bytes) {
    /* return thl */
    char *thl = strndup(&bytes[36],1);
    return thl; 
}

tcp_flags *get_tcp_flags(char *bytes) {
    char *flags = strndup(&bytes[37], 4); // copy 12 bits
    char *flags_bits = hexToBinchar(flags); // read as bin
    free(flags);
    char *reserved = strndup(&flags_bits[0], 6);
    int urg = 0, ack = 0, psh = 0, rst = 0, syn = 0, fin = 0; 
    if (flags_bits[6] == '1') {
        urg = 1;
    }
    if (flags_bits[7] == '1') {
        ack = 1;
    }
    if (flags_bits[8] == '1') {
        psh = 1;
    }
    if (flags_bits[9] == '1') {
        rst = 1;
    }
    if (flags_bits[10] == '1') {
        syn = 1;
    }
    if (flags_bits[11] == '1') {
        fin = 1;
    }
    free(flags_bits);
    return create_tcp_flags(reserved,urg,ack,psh,rst,syn,fin);
}

char *get_window(char *bytes) {
    /* return raw window value in hexadecimal */
    char *window_untrimmed = strndup(&bytes[42],5); // copy 4 bytes of window value
    int length = strlen(window_untrimmed) + 1; 
    char *window_raw = (char *) malloc (length * sizeof(char)); 
    remove_spaces(window_raw,window_untrimmed);
    free(window_untrimmed);
    return window_raw;
}
char *get_checksum(char *bytes) {
    /* return unverified checksum value in hexadecimal */
    char *checksum_untrimmed = strndup(&bytes[48],5); // copy 4 bytes of checksum value
    int length = strlen(checksum_untrimmed) + 1; 
    char *checksum_raw = (char *) malloc (length * sizeof(char)); 
    remove_spaces(checksum_raw,checksum_untrimmed);
    free(checksum_untrimmed);
    return checksum_raw;
}

char *get_urg_pointer(char *bytes) {
    /* return unverified checksum value in hexadecimal */
    char *urgp_untrimmed = strndup(&bytes[54],5); // copy 4 bytes of urgent pointer
    int length = strlen(urgp_untrimmed) + 1; 
    char *urgp_raw = (char *) malloc (length * sizeof(char)); 
    remove_spaces(urgp_raw,urgp_untrimmed);
    free(urgp_untrimmed);
    return urgp_raw;
}

tcp *create_tcp (char *bytes, int *num) {
    /* creates tcp segment from bytes */
    tcp *tcp_seg = (tcp *) calloc(1,sizeof(tcp)); 
    tcp_seg ->num_frame = *num ;
    get_src_dest_port_raw(bytes, &(tcp_seg->src_port), &(tcp_seg->dst_port));
    tcp_seg ->seq_number = get_seq_number_raw(bytes);
    tcp_seg ->ack_number = get_ack_number_raw(bytes); 
    tcp_seg ->thl = get_thl(bytes); 
    tcp_seg ->flags = get_tcp_flags(bytes); 
    tcp_seg ->window = get_window(bytes); 
    tcp_seg ->checksum = get_checksum(bytes); 
    tcp_seg ->urg_pointer = get_urg_pointer(bytes);
    return tcp_seg;
}

tcp_flags *create_tcp_flags(char *reserved, int urg, int ack, int psh, int rst, int syn, int fin) {
    tcp_flags *tflags = (tcp_flags *) calloc(1,sizeof(tcp_flags)); 
    tflags ->reserved = reserved; 
    tflags ->urg = urg; 
    tflags ->ack = ack; 
    tflags ->psh = psh; 
    tflags ->rst = rst; 
    tflags ->syn = syn;
    tflags ->fin = fin; 
    return tflags; 
}

void delete_tcp_flags (tcp_flags *tflags) {
    if (tflags ->reserved) {
        free(tflags->reserved);
    }
    free(tflags); 
}

void delete_tcp (tcp *tcp_seg) {
    /* deletes tcp segment */
    free(tcp_seg ->src_port);
    free(tcp_seg ->dst_port);
    free(tcp_seg ->seq_number);
    free(tcp_seg ->ack_number);
    free(tcp_seg ->thl);
    delete_tcp_flags(tcp_seg->flags);
    free(tcp_seg ->window);
    free(tcp_seg ->checksum);
    free(tcp_seg ->urg_pointer);
    free(tcp_seg);
}

void print_tcp (tcp *tcp_seg) {
    /* prints tcp segment */
    /* this function needs to be completed */
}