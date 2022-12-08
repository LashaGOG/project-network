#include "./headers/frame.h"

frame *create_frame(char *bytes, int *num)
{
    if (bytes == NULL || strcmp(bytes, "") == 0  || strlen(bytes) == 0)
        return NULL;
    
    frame *fr = (frame *) calloc(1, sizeof(frame)); //all the elements of our frame is initialized either to 0 for integers or NULL for pointers

    fr->bytes = strdup(bytes);
    fr->eth = create_eth_frame(bytes, *num);
    if (fr->eth == NULL)
    {
        free(fr);
        return NULL;
    }
    fr->num_frame = ++*num; 
    int val = ++fr->eth->num_frame;
    if (fr->eth->Payload != NULL)
    {
        fr->ip = create_ipv4(fr->eth->Payload, val);
        if (fr->ip != NULL)
        {
            if (fr->ip->Payload != NULL)
            {
                fr->tcp_ = create_tcp(fr->ip->Payload, val);
                if (fr->tcp_ != NULL)
                {
                    if (fr->tcp_->Payload != NULL && (hexToDec(fr->tcp_->src_port) == 80 || hexToDec(fr->tcp_->dst_port) == 80))
                        fr->http = get_http(fr->tcp_->Payload);
                }
            }
        }
    }
    fr->print = 1;
    fr->suiv = NULL;

    return fr;
}

void addLast(frame **head_lst_frames, char *line, int *frame_counter)
{
    //create a new node
    frame *newFrame = create_frame(line,frame_counter);

    newFrame->suiv = NULL;

    //if head is NULL, it is an empty list
    if(*head_lst_frames == NULL)
         *head_lst_frames = newFrame;
    //Otherwise, find the last node and add the newNode
    else
    {
        frame *lastFrame = *head_lst_frames;

        //last node's next address will be NULL.
        while(lastFrame->suiv != NULL)
        {
            lastFrame = lastFrame->suiv;
        }

        //add the newNode at the end of the linked list
        lastFrame->suiv = newFrame;
    }

}

frame *queue_frame (frame **ptr, frame *suiv)
{
    (*ptr)->suiv = suiv;
    *ptr = (*ptr)->suiv;
    return *ptr;
}

void print_frame(frame *ptr)
{
    if (ptr == NULL) {
        puts("The frame is NULL/empty.");
        return;
    }
    // if (ptr->print == 0) 
        // return;

    if (ptr->bytes == NULL || strcmp(ptr->bytes, "") == 0 || strlen(ptr->bytes) == 0) {
        puts("The frame is empty.");
        return;
    }
    
    if (ptr->eth != NULL)
        print_eth_frame(ptr->eth);
    
    if (ptr->ip != NULL)
        print_ipv4(ptr->ip);
    
    if (ptr->tcp_ != NULL)
        print_tcp(ptr->tcp_, 1);

    if (ptr->http != NULL)
        print_http(ptr->http);

    printf("frame->print = %d\n", ptr->print);
}


void print_specific_frame(frame *fr, int frame_number) {
    /* print frame if it's number is frame_number */

    frame *tmp = fr;
    while (tmp) {
        if (tmp ->num_frame == frame_number) {
            print_frame(tmp);

            return;

        }
        tmp = tmp -> suiv;
    }
}

char* filter(frame *ptr)
{
    puts("Before typing your filter, the syntax of the filter is the following : 'filter_expression == value'.");
    puts("Unfortunately, only a very limited choice of filter_expression is available ('ip_address' and 'port' to which you can add '_src' or '_dst' depending on the filter you want to apply).");
    puts("Examples :\n-for an ip address filter : 'ip_address != 192.126.0.12' or 'ip_address_src == 192.126.0.12'");
    puts("-for a TCP port filter : 'port != 2345' or 'port_dst == 2345'\n");

    char* input = verif_input("Enter your filter : ");

    if (strcmp(input, "q") == 0)
    {
        free(input);   
        return NULL;
    }

    frame *tmp = ptr;
    if (strcmp(input, "none") == 0)
    {
        while (tmp)
        {
            tmp->print = 1;
            tmp = tmp->suiv;
        }
    }

    else if (strstr(input, "mac_address") != NULL)
    {
        while (tmp)
        {
            tmp->print = 0;
            tmp = tmp->suiv;
        }
        filter_mac(input, ptr);
    }

    else if (strstr(input, "ip_address") != NULL)
    {
        while (tmp)
        {
            tmp->print = 0;
            tmp = tmp->suiv;
        }
        filter_ip(input, ptr);
    }

    else if (strstr(input, "port"))
    {
        while (tmp)
        {
            tmp->print = 0;
            tmp = tmp->suiv;
        }
        filter_port(input, ptr);
    }

    else if (strstr(input, "double"))
    {
        while (tmp)
        {
            tmp->print = 0;
            tmp = tmp->suiv;
        }
        char *first = verif_input("Enter the first filter : ");
        char *cond = verif_cond("Enter the condition (either && or ||) : ");
        char *second = verif_input("Enter the second filter : ");

        filter_double(first, second, ptr);

        free(first);
        free(second);
        free(input);
        return cond;
    }

    else
    {
        while (tmp)
        {
            tmp->print = 0;
            tmp = tmp->suiv;
        }
        filter_protocol(input, ptr);
    }
    free(input);
    return NULL;
}

//char *verif_input(char *prompt) {
//    while (1) {
//        char input[256];
//        printf("%s", prompt);
//        
//        fgets(input, 256, stdin);
//        input[strcspn(input, "\n")] = 0;    
//
//        regex_t protocol_regex, ip_port_mac_regex, q_none_regex;
//        regcomp(&protocol_regex, "^(ethernet|eth|ipv4|ip|tcp|http)$", REG_EXTENDED);
//        regcomp(&ip_port_mac_regex, "^(ip_address|port|mac_address)(_src|_dst)? (==|!=) .*$", REG_EXTENDED);
//        regcomp(&q_none_regex, "^(q|none|double)$", REG_EXTENDED);
//
//        if (!regexec(&protocol_regex, input, 0, NULL, 0)) {
//            regfree(&protocol_regex);
//            regfree(&ip_port_mac_regex);
//            regfree(&q_none_regex);
//            return strdup(input);
//        }
//
//        if (!regexec(&ip_port_mac_regex, input, 0, NULL, 0)) {
//            regfree(&protocol_regex);
//            regfree(&ip_port_mac_regex);
//            regfree(&q_none_regex);
//            return strdup(input);
//        }
//
//        if (!regexec(&q_none_regex, input, 0, NULL, 0)) {
//            regfree(&protocol_regex);
//            regfree(&ip_port_mac_regex);
//            regfree(&q_none_regex);
//            return strdup(input);
//        } 
//        puts("Input does not respect the syntax.");
//        regfree(&protocol_regex);
//        regfree(&ip_port_mac_regex);
//        regfree(&q_none_regex);
//    }
//}
char *verif_input(char *prompt) {
    while (1) {
        char input[256];
        printf("%s", prompt);
        
        fflush(stdin);

        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "ethernet") == 0 || strcmp(input, "eth") == 0 ||
            strcmp(input, "ipv4") == 0 || strcmp(input, "ip") == 0 ||
            strcmp(input, "tcp") == 0 || strcmp(input, "http") == 0) {
            return strdup(input);
        }

        if (strstr(input, "ip_address") || strstr(input, "port") || strstr(input, "mac_address")) {
            if (strstr(input, "==") || strstr(input, "!=")) {
                return strdup(input);
            }
        }

        if (strcmp(input, "q") == 0 || strcmp(input, "none") == 0 || strcmp(input, "double") == 0) {
            return strdup(input);
        }

        puts("Input does not respect the syntax.");
    }
}

char *verif_cond(char *prompt)
{
    while (1)
    {
        char input[3];
        printf("%s", prompt);

        fflush(stdin);

        fgets(input, 3, stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "&&") == 0 || strcmp(input, "||") == 0)
            return strdup(input);

        puts("Value can be either '&&' or '||'. Please, try again.");
    }
}

void filter_double(char* first, char* second, frame* ptr)
{
    if (strstr(first, "mac_address") != NULL)
    {
        filter_mac(first, ptr);
    }
    else if (strstr(first, "ip_address") != NULL)
    {
        filter_ip(first, ptr);
    }
    else if (strstr(first, "port"))
    {
        filter_port(first, ptr);
    }
    else 
    {
        filter_protocol(first, ptr);
    }

    if (strstr(second, "mac_address") != NULL)
    {
        filter_mac(second, ptr);
    }
    else if (strstr(second, "ip_address") != NULL)
    {
        filter_ip(second, ptr);
    }
    else if (strstr(second, "port"))
    {
        filter_port(second, ptr);
    }
    else 
    {
        filter_protocol(second, ptr);
    }
}

void filter_protocol(char *str, frame *ptr)
{
    frame *tmp = ptr;
    while (tmp)
    {
        if (strncmp("eth", str, 3) == 0)
        {
            if (tmp->eth != NULL)
            {
                tmp->print += 1;
            }
            // else
            // {
            //     tmp->print = 0;
            // }
        }
        else if (strncmp("ip", str, 2) == 0)
        {
            if (tmp->ip != NULL)
            {
                tmp->print += 1;
            }
            // else
            // {
            //     tmp->print = 0;
            // }
        }
        else if (strncmp("tcp", str, 3) == 0)
        {
            if (tmp->tcp_ != NULL && tmp->http == NULL)
            {
                tmp->print += 1;
            }
            // else 
            // {
            //     tmp->print = 0;
            // }
        }
        else if (strncmp("http", str, 4) == 0)
        {
            if  (tmp->http != NULL)
            {
                tmp->print += 1;
            }
            // else
            // {
            //     tmp->print = 0;
            // }
        }
        tmp = tmp->suiv;
    }   
}

void filter_mac(char *str, frame *ptr)
{
    frame *tmp = ptr;
    char *eq = strstr(str, "==");
    char *neq = strstr(str, "!=");
    char *mac =  NULL;
    if (eq != NULL)
    {
        mac = strdup(&eq[3]);
    }
    else{
        mac = strdup(&neq[3]);
    }

    while (tmp)
    {
        if (tmp->eth != NULL)
        {
            char *temp1 = tmp->eth->src_mac;
            char *temp2 = tmp->eth->dest_mac;
            if (eq != NULL)
            {
                if (strstr(str, "src"))   //ip_address_src  == ...
                {  
                    if (strcmp(mac, temp1) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 0;
                    // }
                }
                else if (strstr(str, "dst"))  //ip_address_dst  == ...
                {
                    if (strcmp(mac, temp2) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 0;
                    // }
                }
                else    //ip_address  == ...
                {
                    if (strcmp(mac, temp1) == 0 || strcmp(mac, temp2) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
            }
            else    //ip_address... != ...
            {
                if (strstr(str, "src"))   //ip_address_src != ...
                {
                    if (strcmp(mac, temp1) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else if (strstr(str, "dst"))  //ip_address_src != ...
                {
                    if (strcmp(mac, temp2) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else{
                    if (strcmp(mac, temp1) != 0 && strcmp(mac, temp2) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
            }
        }
        tmp = tmp->suiv; 
    }
    free(mac);
}

void filter_ip(char *str, frame *ptr)
{
    frame *tmp = ptr;
    char *eq = strstr(str, "==");
    char *neq = strstr(str, "!=");
    char *ip = NULL;
    if (eq != NULL)
    {
        ip = strdup(&eq[3]);
    }
    else{
        ip = strdup(&neq[3]);
    }

    while (tmp)
    {
        if (tmp->ip != NULL)
        {
            char *temp1 = hex_to_ip(tmp->ip->src_ip);
            char *temp2 = hex_to_ip(tmp->ip->dest_ip);
            if (eq != NULL)
            {
                if (strstr(str, "src"))   //ip_address_src  == ...
                {  
                    if (strcmp(ip, temp1) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else if (strstr(str, "dst"))  //ip_address_dst  == ...
                {
                    if (strcmp(ip, temp2) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else    //ip_address  == ...
                {
                    if (strcmp(ip, temp1) == 0 || strcmp(ip, temp2) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
            }
            else    //ip_address... != ...
            {
                if (strstr(str, "src"))   //ip_address_src != ...
                {
                    if (strcmp(ip, temp1) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else if (strstr(str, "dst"))  //ip_address_src != ...
                {
                    if (strcmp(ip, temp2) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else{
                    if (strcmp(ip, temp1) != 0 && strcmp(ip, temp2) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
            }
            free(temp1);
            free(temp2);
        }
        tmp = tmp->suiv; 
    }
    free(ip);
}
           
void filter_port(char* str, frame *ptr)
{
    frame *tmp = ptr;
    char *eq = strstr(str, "==");
    char *neq = strstr(str, "!=");
    char *tcpport = NULL;
    if (eq != NULL)
    {
        tcpport = strdup(&eq[3]);
    }
    else{
        tcpport = strdup(&neq[3]);
    }
    while (tmp)
    {
        if (tmp->tcp_ != NULL)
        {
            char *temp1 = hexToDec_c(tmp->tcp_->src_port);
            char *temp2 = hexToDec_c(tmp->tcp_->dst_port);
            if (eq != NULL)
            {
                if (strstr(str, "src"))   //ip_address_src  == ...
                {  
                    if (strcmp(tcpport, temp1) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else if (strstr(str, "dst"))  //ip_address_dst  == ...
                {
                    if (strcmp(tcpport, temp2) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else    //ip_address  == ...
                {
                    if (strcmp(tcpport, temp1) == 0 || strcmp(tcpport, temp2) == 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
            }
            else    //port... != ...
            {
                if (strstr(str, "src"))   //port_src != ...
                {
                    if (strcmp(tcpport, temp1) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else if (strstr(str, "dst"))  //port_dst != ...
                {
                    if (strcmp(tcpport, temp2) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
                else{       //port != ...
                    if (strcmp(tcpport, temp1) != 0 && strcmp(tcpport, temp2) != 0)
                    {
                        tmp->print += 1;
                    }
                    // else
                    // {
                    //     tmp->print = 1;
                    // }
                }
            }
            free(temp1);
            free(temp2);
        }
        tmp = tmp->suiv; 
    }
    free(tcpport);
}

void delete_frame(frame *fr)
{
    if (fr != NULL)
    {
        delete_frame(fr->suiv);
        free(fr->bytes);
        if (fr->eth != NULL)
            delete_eth_frame(fr->eth);
        if (fr->ip != NULL)
            delete_ipv4(fr->ip);
        if (fr->tcp_ != NULL)
            delete_tcp(fr->tcp_);
        if (fr->http != NULL)
            delete_http(fr->http);
        fr->suiv = NULL;
        free(fr);
    }
    else
    {
        return;
    }
}

void delete_linked_frames(frame *fr)
{
    delete_linked_frames(fr->suiv);
    delete_frame(fr);
}
