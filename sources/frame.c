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
                    if (fr->tcp_->Payload != NULL)
                        fr->http = get_http(fr->tcp_->Payload);
                }
            }
        }
    }
    fr->print = 1;
    fr->suiv = NULL;

    return fr;
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
    if (ptr->print == 0) 
        return;

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
}

char *filter(frame *ptr)
{
    frame *tmp = ptr;
    puts("Before typing your filter, the syntax of the filter is the following : 'filter_expression == value'.");
    puts("Unfortunately, only a very limited choice of filter_expression is available ('ip_address' and 'port' to which you can add '_src' or '_dst' depending on the filter you want to apply).");
    puts("Examples :\n-for an ip address filter : 'ip_address != 192.126.0.12' or 'ip_address_src == 192.126.0.12'");
    puts("-for a TCP port filter : 'port != 2345' or 'port_dst == 2345'\n");

    char* input = verif_input("Enter your filter : ");

    if (strcmp(input, "q") == 0)
            return NULL;
    if (strcmp(input, "none") == 0)
    {
        while (tmp)
        {
            tmp->print = 1;
            tmp = tmp->suiv;
        }
    }
    else if (strstr(input, "ip_address") != NULL)
    {
        filter_ip(input, ptr);
    }

    else if (strstr(input, "port"))
    {
        filter_port(input, ptr);
    }

    return input;
}

char *verif_input(char *prompt) {
    while (1) {
        char input[256];
        printf("%s", prompt);
        
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = 0;    

        regex_t ip_port_regex, q_none_regex;
        regcomp(&ip_port_regex, "^(ip_address|port)(_src|_dst)? (==|!=) .*$", REG_EXTENDED);
        regcomp(&q_none_regex, "^(q|none)$", REG_EXTENDED);

        if (!regexec(&ip_port_regex, input, 0, NULL, 0)) {
            regfree(&ip_port_regex);
            regfree(&q_none_regex);
            return strdup(input);
        }

        if (!regexec(&q_none_regex, input, 0, NULL, 0)) {
            regfree(&ip_port_regex);
            regfree(&q_none_regex);
            return strdup(input);
        } 
        puts("Input doesn't respect the syntax.");
    }
}

void filter_ip(char *str, frame *ptr)
{
    frame *tmp = ptr;
    char *ip = strdup(&str[3]);
    char *eq = strstr(str, "==");

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
                    if (strcmp(ip, temp1) != 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
                else if (strstr(str, "dst"))  //ip_address_dst  == ...
                {
                    if (strcmp(ip, temp2) != 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
                else    //ip_address  == ...
                {
                    if (strcmp(ip, temp1) != 0 && strcmp(ip, temp2) != 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
            }
            else    //ip_address... != ...
            {
                if (strstr(str, "src"))   //ip_address_src != ...
                {
                    if (strcmp(ip, temp1) == 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
                else if (strstr(str, "dst"))  //ip_address_src != ...
                {
                    if (strcmp(ip, temp2) == 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
                else{
                    if (strcmp(ip, temp1) == 0 || strcmp(ip, temp2) == 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
            }
            free(temp1);
            free(temp2);
        }
        tmp = tmp->suiv; 
    }
}
           
void filter_port(char* str, frame *ptr)
{
    frame *tmp = ptr;
    char *tcpport = strdup(&str[3]);
    char *eq = strstr(str, "==");

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
                    if (strcmp(tcpport, temp1) != 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
                else if (strstr(str, "dst"))  //ip_address_dst  == ...
                {
                    if (strcmp(tcpport, temp2) != 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
                else    //ip_address  == ...
                {
                    if (strcmp(tcpport, temp1) != 0 && strcmp(tcpport, temp2) != 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
            }
            else    //port... != ...
            {
                if (strstr(str, "src"))   //port_src != ...
                {
                    if (strcmp(tcpport, temp1) == 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
                else if (strstr(str, "dst"))  //port_src != ...
                {
                    if (strcmp(tcpport, temp2) == 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
                else{       //port != ...
                    if (strcmp(tcpport, temp1) == 0 || strcmp(tcpport, temp2) == 0)
                    {
                        tmp->print = 0;
                    }
                    else
                    {
                        tmp->print = 1;
                    }
                }
            }
            free(temp1);
            free(temp2);
        }
        tmp = tmp->suiv; 
    }
}

void delete_frame(frame *fr)
{
    if (fr != NULL)
    {
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
}

void delete_linked_frames(frame *fr)
{
    frame *tmp;
    while (fr)
    {
        tmp = fr;
        fr = fr->suiv;
        delete_frame(tmp);
    }
}