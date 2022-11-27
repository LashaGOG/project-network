#include "./headers/ipv4.h"

char *get_ip_version (char *bytes){
    char *ip =  strndup(&bytes[0], 1); //copy 4 bits
    return ip;
}

char *get_header_length (char *bytes){
    char *header_length = strndup(&bytes[1], 1);  //copy 4 bits
    return header_length;
}

tos *get_TOS (char *bytes){
    char *TOS = strndup(&bytes[3], 2);  //copy 1 byte
    char *TOS_bits = hexToBinchar(TOS);
    char *Precedence = (char *) calloc(21, sizeof(char));
    int delay = 0, throughput = 0, reliability = 0, cost = 0, reserved = 0;
    free(TOS);
    if (TOS_bits[0] == '0') {           //First 3 bits = Precedence
        if (TOS_bits[1] == '0') {
            if (TOS_bits[2] == '0') {
                Precedence = "Routine";
            }
            else{
                Precedence = "Priority";
            }
        }
        else{
            if (TOS_bits[2] == '0'){
                Precedence = "Immediate";
            }
            else{
                Precedence = "Flash";
            }
        }
    }
    else{
        if (TOS_bits[1] == '0') {
            if (TOS_bits[2] == '0') {
                Precedence = "Flash Override";
            }
            else{
                Precedence = "CRITIC/ECP";
            }
        }
        else{
            if (TOS_bits[2] == '0'){
                Precedence = "Internetwork Control";
            }
            else{
                Precedence = "Network Control";
            }
        }
    }
    Precedence = realloc(Precedence, strlen(Precedence) + 1);

    if (TOS_bits[3] == '1')
        delay = 1;
    if (TOS_bits[4] == '1')
        throughput = 1;
    if (TOS_bits[5] == '1')
        reliability = 1;
    if (TOS_bits[6] == '1')
        cost = 1;
    if (TOS_bits[7] == '1'){
        reserved = 1;           //Problem to handle, the reserved bit should always be 0
    }
    free(TOS_bits);

    return create_tos(Precedence, delay, throughput, reliability, cost, reserved);
}

char* get_total_length (char* bytes) {
    char* tot_length = strndup(&bytes[6], 5);
    return tot_length;
}

char* get_identifier (char* bytes) {
    char* identifier = strndup(&bytes[12], 5);
    return identifier;
}