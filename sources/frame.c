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
    fr->print = 0;
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
    if (ptr->bytes == NULL || strcmp(ptr->bytes, "") == 0 || strlen(ptr->bytes) == 0) {
        puts("The frame is empty.");
        return;
    }
    wprintf(L"Frame n°%d : %s\n", ptr->num_frame, ptr->bytes);
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