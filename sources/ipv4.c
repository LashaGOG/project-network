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
    char *Precedence;
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

fragmentation *get_fragmentation (char *bytes) {
    char *fragment = strndup(&bytes[18], 5);
    char *fragment_bits = hexToBinchar(fragment);
    free(fragment);
    
    int R = 0, DF = 0, MF = 0;
    if (fragment_bits[0] == '1')
        R = 1;
    if (fragment_bits[1] == '1')
        DF = 1;
    if (fragment_bits[2] == '1')
        MF = 1;
    
    char *offset = strndup(&fragment_bits[3], 13);

    free(fragment_bits);
    return create_fragmentation(R, DF, MF, offset);
}

char *get_ttl (char *bytes) {
    char* ttl = strndup(&bytes[24], 2);
    return ttl;
}

char *get_protocol (char *bytes) {
    char *protocol = strndup(&bytes[27], 2);
    return protocol;
}

char *get_header_checksum (char *bytes) {
    char *checksum = strndup(&bytes[30], 5);
    return checksum;
}

char *get_ip (char* bytes) {
    char *ip_add = strndup(bytes, 11);
    change_separator_str(ip_add,' ','.');
    return ip_add;
}

void get_src_dest_ip (char *bytes, char **ip_src, char **ip_dest) {
    *(ip_src) = get_ip(&bytes[36]);
    *(ip_dest) = get_ip(&bytes[48]);
}

ipv4 *create_ipv4(char* bytes, int *num) {
    ipv4 *ipf = (ipv4*) calloc(1, sizeof(ipv4));
    ipf->num_frame = *num;
    ipf->version = get_ip_version(bytes);
    ipf->header_length =  get_header_length(bytes);
    ipf->typesos = get_TOS(bytes);
    ipf->total_length = get_total_length(bytes);
    ipf->identifier = get_identifier(bytes);
    ipf->fragment = get_fragmentation(bytes);
    ipf->ttl = get_ttl(bytes);
    ipf->protocol = get_protocol(bytes);
    ipf->header_checksum = get_header_checksum(bytes);
    get_src_dest_ip(bytes, &(ipf->src_ip), &(ipf->dest_ip));
    return ipf;
}

fragmentation *create_fragmentation(int R, int DF, int MF, char *offset) {
    fragmentation *fragment = (fragmentation*) calloc(1, sizeof(fragmentation));
    fragment->R = R;
    fragment->DF = DF;
    fragment->MF = MF;
    fragment->offset = offset;
    return fragment;
}

tos *create_tos (char *precedence, int delay, int throughput, int reliability, int cost, int reserved) {
    tos *typesos = (tos*) calloc(1, sizeof(tos));
    typesos->precedence = strdup(precedence);
    typesos->delay = delay;
    typesos->throughput = throughput;
    typesos->reliability = reliability;
    typesos->cost = cost;
    typesos->reserved = reserved;
    return typesos;
}

void delete_ipv4 (ipv4 *ipf) {
    free(ipf->version);
    free(ipf->header_length);
    delete_tos(ipf->typesos);
    free(ipf->total_length);
    free(ipf->identifier);
    delete_fragmentation(ipf->fragment);
    free(ipf->ttl);
    free(ipf->protocol);
    free(ipf->header_checksum);
    free(ipf->src_ip);
    free(ipf->dest_ip);
    free(ipf);
}

void delete_fragmentation (fragmentation *fragment) {
    if (fragment->offset)
        free(fragment->offset);
    free(fragment);
}

void delete_tos (tos *typesos) {
    if (typesos->precedence)
        free(typesos->precedence);
    free(typesos);
}

void print_ipv4(ipv4 *ipf) {
    char temp[10];
    size_t len = 10;
    puts("__________ COUCHE IP _________");
    printf("IP addresses :\n     -Source : %s\n     -Destination : %s\n", ipf->src_ip, ipf->dest_ip);
   
    hexToBin(ipf->header_length);
    printf(" = Header length : %d bytes (%d)\n", (hexToDec(ipf->header_length) * 4) , hexToDec(ipf->header_length));
   
    printf("Type of Service (TOS) :\n     -Precedence : %s\n     -Delay, throughput, reliability, cost, reserved : %d, %d, %d, %d, %d\n", ipf->typesos->precedence, ipf->typesos->delay, ipf->typesos->throughput, ipf->typesos->reliability,  ipf->typesos->cost, ipf->typesos->reserved);
    
    remove_spaces(temp, ipf->total_length);
    printf("Total length : %d\n", hexToDec(temp));
    
    mem_reset(temp, len);
    remove_spaces(temp, ipf->identifier);
    printf("Identification : 0x%s (%d)\n", temp, hexToDec(temp));
    
    printf("Fragmentation :\n    -Flags...\n    -%s = Fragment offset : %d\n", ipf->fragment->offset, binToDec(ipf->fragment->offset)); 

    printf("Time to Live (TTL) : %d\n", hexToDec(ipf->ttl));
    
    if (strcmp("06", ipf->protocol) != 0) {
        printf("Protocol not supported.");
    }
    else {
        printf("Protocol :  TCP (6)");
    }
    puts("");
    
    remove_spaces(temp, ipf->header_checksum);
    printf("Header Checksum : 0x%s\n", temp);
}