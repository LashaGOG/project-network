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
    char *val_hexa_flags = strndup(&bytes[37], 4); // copy 12 bits
    char *flags_bits = hexToBinchar(val_hexa_flags); // read as bin

    char *reserved = strndup(&flags_bits[0], 6);
    int length = strlen(val_hexa_flags) + 1;
    char *val_hexa_without_space = (char *) calloc (length,sizeof(char));
    remove_spaces(val_hexa_without_space,val_hexa_flags);
    free(val_hexa_flags);
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
    return create_tcp_flags(reserved,val_hexa_without_space,urg,ack,psh,rst,syn,fin);
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

tcp_flags *create_tcp_flags(char *reserved, char *val_hx, int urg, int ack, int psh, int rst, int syn, int fin) {
    tcp_flags *tflags = (tcp_flags *) calloc(1,sizeof(tcp_flags)); 
    tflags -> val_hexa = val_hx;
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
    if (tflags ->val_hexa) {
        free(tflags -> val_hexa);
    }
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

void print_tcp_flags (tcp_flags *tflags) {
        printf ("Flags : 0x%s \n",tflags->val_hexa);

        if (strncmp(tflags->reserved,"000",3) == 0) {
            printf ("\t%s...... = reserved (Not Set) \n", tflags->reserved);
        }
        else if (strncmp(tflags->reserved,"111",3) == 0){
            printf ("\t%s...... = reserved (Set) \n", tflags->reserved);
        }
        
        if (tflags->urg == 1) {
            printf ("\t......%d..... = Urgent (Set) \n", tflags->urg);
        } 
        else {
            printf ("\t......%d..... = Urgent (Not Set) \n", tflags->urg);
        }
        if (tflags->ack == 1) {
            printf ("\t.......%d.... = Acknowledgement (Set) \n", tflags->ack);
        } 
        else {
            printf ("\t.......%d.... = Acknowledgement (Not Set) \n", tflags->ack);
        }
        
        if (tflags->psh == 1) {
            printf ("\t........%d... = Push (Set) \n", tflags->psh);
        } 
        else {
            printf ("\t........%d... = Push (Not Set) \n", tflags->psh);
        }

        if (tflags->rst == 1) {
            printf ("\t.........%d.. = Reset (Set) \n", tflags->rst);
        } 
        else {
            printf ("\t.........%d.. = Reset (Not Set) \n", tflags->rst);
        }

        if (tflags->syn == 1) {
             printf ("\t..........%d. = Syn (Set) \n", tflags->syn);
        } 
        else {
             printf ("\t..........%d. = Syn (Not Set) \n", tflags->syn);
        }

        if (tflags->fin == 1) {
            printf ("\t...........%d = Fin (Set) \n", tflags->fin);
        } 
        else {
            printf ("\t...........%d = Fin (Not Set) \n", tflags->fin);
        }

}

void print_tcp (tcp *tcp_seg,int print_details) {
    /* prints tcp segment */
    printf ("Transmission Control Protocol, Src Port : %s, Dst port : %s, Seq : %s, Ack : %s \n",hexToDec_c(tcp_seg->src_port), hexToDec_c(tcp_seg->dst_port), tcp_seg->seq_number, tcp_seg ->ack_number); 

    if (print_details == 1) { // print TCP details if print_details is set to 1 
        printf ("TCP DETAILS : \n"); 
        printf ("Source Port : %d (0x%s)\n", hexToDec(tcp_seg->src_port), tcp_seg->src_port);
        printf ("Destination port : %d (0x%s)\n", hexToDec(tcp_seg->dst_port), tcp_seg->dst_port);
        printf ("Sequence number: %lu (0x%s)\n", hexToUnsLong(tcp_seg->seq_number), tcp_seg->seq_number);
        printf ("Acknowledgement number : %lu (0x%s)\n", hexToUnsLong(tcp_seg->ack_number), tcp_seg->ack_number);
        printf ("Data offset (THL) : %d (0x%s)\n", hexToDec(tcp_seg->thl), tcp_seg->thl);
        print_tcp_flags(tcp_seg->flags);
        printf ("Window : %d (0x%s)\n", hexToDec(tcp_seg->window), tcp_seg->window);
        printf ("Checksum : %d (0x%s)\n", hexToDec(tcp_seg->checksum), tcp_seg->checksum);
        printf ("Urgent pointer : %d (0x%s)\n", hexToDec(tcp_seg->urg_pointer), tcp_seg->urg_pointer);
        // OPTIONS + PADDING IS MISSING Hihi
    }
}