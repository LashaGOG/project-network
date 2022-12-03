#include "./headers/flowGraph.h"

void print_heading_row() {
    printf("+-----+---------------------+---------------------------------------------+---------------------+\n");
    printf("| N   | IP SOURCE           |                                             | IP DESTINATION      |\n");
    printf("+-----+---------------------+---------------------------------------------+---------------------+\n");
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
    ipv4 *ipv4_frame = create_ipv4(eFrame->Payload,frame_counter); 
    printf("|     |                           TCP et Trucs ICI                                              |\n");
    printf("| %d  |  %s    ------------------------------------------------->       %s    |\n",eFrame ->num_frame, ipv4_frame->src_ip, ipv4_frame->dest_ip);
    printf("|     |                           des trucs en plus?                                            |\n");
    printf("+-----------------------------------------------------------------------------------------------+\n");

    // delete_ipv4(ipv4_frame);
    delete_eth_frame(eFrame);
}