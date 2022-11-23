#include "./headers/ethernet.h"

char* get_mac_address(char *bytes) {
    /* Returns properly formatted MAC address (6 bytes extracted from bytes) */
    
    char *adress_mac = strndup(bytes,17); // copy 6 bytes 
    change_separator_str(adress_mac,' ',':'); // change ' ' to ':'
    return adress_mac;
}

void get_mac_dest_src (char *bytes, char **mac_src, char **mac_dst) {
    /* initialize mac_src and mac_dst */
    *(mac_src) = get_mac_address(&bytes[0]);
    *(mac_dst) = get_mac_address(&bytes[18]);
}

char* get_eth_proto (char *bytes) {
    /* return ethernet protocl type from ethernet frame*/
    char *ch1 = strndup(&bytes[36],2); // copy 2 bytes 
    char *ch2 = strndup(&bytes[39],2); // copy 2 bytes 

    int length = strlen(ch1) + strlen(ch2);  

    char *proto = (char *) malloc ((length + 1) * sizeof(char)); 
    strcpy(proto,ch1);
    strcat(proto,ch2);
    free(ch1);
    free(ch2);
    return proto;
}

eth_frame *create_eth_frame (char *bytes, int *num) {
    /* créer et initialiser trame ethernet */
    eth_frame *ef = (eth_frame *) malloc (sizeof (eth_frame));
    ef -> num_frame = *num;
    ef -> proto = get_eth_proto (bytes); 
    get_mac_dest_src(bytes, &(ef->src_mac), &(ef->dest_mac)); 
    return ef;
} 

void print_eth_frame (eth_frame *ef) {
    /* afficher trame ethernet */
    printf("Frame %d :\n",ef->num_frame);
    printf("Mac destination : %s\n",ef->dest_mac);
    printf("Mac source : %s\n",ef->src_mac);
    printf("Protocole : Ox%s\n",ef->proto);
}

void delete_eth_frame (eth_frame *ef) {
    /* supprimer trame ethernet */
    free(ef->src_mac);
    free(ef->dest_mac);
    free(ef->proto);
    free(ef);
}