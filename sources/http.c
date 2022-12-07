#include "./headers/http.h"

char *separate_chunks(char *bytes, char **ptr) {
    if (strncmp("0d 0a", bytes, 5) == 0)
        return NULL;
    *ptr = strstr(bytes,"0d 0a");
    if (*ptr == NULL || strcmp(bytes, "") == 0 || strlen(bytes) < 2)
        return NULL;

    if (*ptr[0] == bytes[0] && *ptr[1] == bytes[1])
    {
        if (*ptr[3]  == bytes[3] && *ptr[4] == bytes[4])
            return NULL;
    }
    int length = strlen(bytes) - strlen(*ptr); 
    *ptr += 6; 
    char *rep = strndup(bytes,length);
    return rep; 
}

header *get_header (char *bytes) {
    //printf("bytes : %s\n", bytes);
    int i = 0, j = 1, k = 0;
    int pos = 0;
    char *meth_ver;
    char *uri_stat;
    char *ver_msg;

    while (j < (int) strlen(bytes))
    {
        if (bytes[i] == '2' && bytes[j] == '0')
        {               
            if (k == 1) {
                uri_stat = (char *) calloc(i - pos, sizeof(char));
                strncpy(uri_stat, &bytes[pos], (i - pos - 1));
                //printf("uri_stat = %s\n", uri_stat);

                ver_msg = calloc(strlen(bytes) - (j + 1), sizeof(char));
                strncpy(ver_msg, &bytes[j+2], (strlen(bytes) - (j + 2)));
                //printf("ver_msg = %s\n", ver_msg);
                break;
            }
            if (k == 0) {
                meth_ver = (char  *) calloc(i, sizeof(char));
                strncpy(meth_ver, &bytes[0], (i - 1));
                //printf("meth_ver = %s\n", meth_ver);
                pos = j+2;
                k++;
            }
        }
        i++;
        j++;
    }
    return create_header(meth_ver, uri_stat, ver_msg);
}

champ *get_champ (char *bytes) {
    int i = 0, j = 1;
    int pos = 0;
    char *entete;
    char *valeur;

    while (j < (int) strlen(bytes) - 2)
    {
        if (bytes[i] == '2' && bytes[j] == '0')
        {
            entete = strndup(&bytes[pos], (i - 1));
            
            valeur = strndup(&bytes[j+2], (strlen(bytes) - (j + 2)));
            break;
        }
        i++;
        j++;
    }
    return create_champ(entete, valeur);
}

char *get_corps(char* bytes)
{
    char *str = strstr(bytes, "0d 0a 0d 0a");
    if (strlen(str) < 13)
        return NULL;
    return strdup(&str[12]);
}

e_http *get_http(char *bytes) {
    if (strstr(bytes, "0d 0a 0d 0a") == NULL)
        return NULL;

    char *corps = get_corps(bytes);

    char *ptr1 = bytes;
    char *ptr2;
    char *str = separate_chunks(bytes, &ptr1);
    int first = 0;

    header *entete;
    champ *first_champ;
    
    while (str != NULL &&  strcmp(str, "") != 0)
    {
        if (first == 0) {
            first = 1;
            entete = get_header(str);
            free(str);

            ptr2 = ptr1;
            str = separate_chunks(ptr2, &ptr1);
            continue;
        }
        if  (first == 1)
        {
            first = 2;

            first_champ = get_champ(str);
            free(str);
            
            ptr2 = ptr1;
            str = separate_chunks(ptr2, &ptr1);
            continue;
        }
        champ *tmp = get_champ(str);
        queue_champ(first_champ, tmp);
        free(str);
        
        ptr2 = ptr1;
        str = separate_chunks(ptr2, &ptr1);     
    }
    ptr1 = NULL;
    ptr2 = NULL;
    return create_http(entete, first_champ, corps);
}

champ *create_champ(char *entete, char *valeur) {
    champ *ptr = (champ *) calloc(1, sizeof(champ));
    ptr->entete = entete;
    ptr->valeur = valeur;
    ptr->suivant = NULL;
    return ptr;
}

void queue_champ (champ *ptr, champ *suiv)
{
    if (!ptr->suivant)
    {
        ptr->suivant = suiv;
        return;
    }
    queue_champ(ptr->suivant, suiv);
}

header *create_header(char *meth_ver, char *uri_stat, char *ver_msg)
{
    header *ptr = (header *) calloc(1, sizeof(header));
    ptr->meth_ver = meth_ver;
    ptr->uri_stat = uri_stat;
    ptr->ver_msg = ver_msg;
    return ptr;
}

e_http *create_http (header *he, champ *ch, char *corps)
{
    e_http *ptr = (e_http *) calloc(1, sizeof(e_http));
    ptr->http_header = he;
    ptr->champs = ch;
    ptr->corps = corps;
    return ptr;
}

void print_header(header *entete)
{
    char *ent1 = hexToChar(entete->meth_ver);
    char *ent2 = hexToChar(entete->uri_stat);
    char *ent3 = hexToChar(entete->ver_msg);
    if (ent1 == NULL || ent2 == NULL || ent3 == NULL) puts("nsm\n");
    if (strcmp("HTTP", ent1) == 0)
    {
        printf("Response Version : %s\nStatus code : %s\n, Response Phrase : %s\n", ent1, ent2, ent3);
    }
    else
    {
        printf("Request Method : %s\nRequest URI : %s\nRequest Version : %s\n", ent1, ent2, ent3);
    }
    free(ent1);
    free(ent2);
    free(ent3);
}

void print_champ(champ *first)
{
    champ* tmp = first;
    while (tmp)
    {
        if (tmp->entete && tmp->valeur)
        {
            char *entete = hexToChar(tmp->entete);
            char *value =  hexToChar(tmp->valeur);
            printf("\t%s %s\n", entete, value);
            free(entete);
            free(value);
        }
        tmp = tmp->suivant;
    }
}

void print_http(e_http *ptr)
{
    puts("\n_________ COUCHE  HTTP _________");
    puts("   Hypertext transfer protocol  ");
    print_header(ptr->http_header);
    print_champ(ptr->champs);
    char *corps = hexToChar(ptr->corps);
    printf("%s\n", corps);
    free(corps);
}

void delete_header(header *ptr)
{
    free(ptr->meth_ver);
    free(ptr->uri_stat);
    free(ptr->ver_msg);
    free(ptr);
}

void delete_champ(champ *ptr) 
{
    if (!ptr)
        return;
    delete_champ(ptr->suivant);
    free(ptr->entete);
    free(ptr->valeur);
    free(ptr);
}

void delete_http(e_http *ptr)
{
    delete_champ(ptr->champs);
    delete_header(ptr->http_header);
    free(ptr->corps);
    free(ptr);
}

void fprint_header(FILE *fd, header *entete)
{
    char *ent1 = hexToChar(entete->meth_ver);
    char *ent2 = hexToChar(entete->uri_stat);
    char *ent3 = hexToChar(entete->ver_msg);
    if (strcmp("HTTP", ent1) == 0)
    {
        fprintf(fd, "Response Version : %s\nStatus code : %s\n, Response Phrase : %s\n", ent1, ent2, ent3);
    }
    else
    {
        fprintf(fd, "Request Method : %s\nRequest URI : %s\nRequest Version : %s\n", ent1, ent2, ent3);
    }
    free(ent1);
    free(ent2);
    free(ent3);
}

void fprint_champ(FILE *fd, champ *first)
{
    champ* tmp = first;
    while (tmp)
    {
        if (tmp->entete && tmp->valeur)
        {
            char *entete = hexToChar(tmp->entete);
            char *value =  hexToChar(tmp->valeur);
            fprintf(fd, "\t%s %s\n", entete, value);
            free(entete);
            free(value);
        }
        tmp = tmp->suivant;
    }
}

void fprint_http(FILE *fd, e_http *ptr)
{
    fputs("\n_________ COUCHE  HTTP _________", fd);
    fputs("   Hypertext transfer protocol  ", fd);
    fprint_header(fd, ptr->http_header);
    fprint_champ(fd, ptr->champs);
    char *corps = hexToChar(ptr->corps);
    fprintf(fd, "%s\n", corps);
    free(corps);
}