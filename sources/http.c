#include "./headers/http.h"

char *separate_chunks(char *bytes, char **ptr) {
    *ptr = strstr(bytes,"0d 0a");
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
                printf("uri_stat = %s\n", uri_stat);

                ver_msg = calloc(strlen(bytes) - (j + 1), sizeof(char));
                strncpy(ver_msg, &bytes[j+2], (strlen(bytes) - (j + 2)));
                printf("ver_msg = %s\n", ver_msg);
                break;
            }
            if (k == 0) {
                meth_ver = (char  *) calloc(i, sizeof(char));
                strncpy(meth_ver, &bytes[0], (i - 1));
                printf("meth_ver = %s\n", meth_ver);
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

    while (j < (int) strlen(bytes))
    {
        if (bytes[i] == '2' && bytes[j] == '0')
        {
            entete = (char *) calloc(i, sizeof(char));
            strncpy(entete, &bytes[pos], (i - 1));
            
            valeur = calloc(strlen(bytes) - (j + 1), sizeof(char));
            strncpy(valeur, &bytes[j+2], (strlen(bytes) - (j + 2)));
        }
        i++;
        j++;
    }
    return create_champ(entete, valeur);
}

e_http *get_http(char *bytes) {
    char *ptr1 = bytes;
    char *ptr2;
    char *str = separate_chunks(bytes, &ptr1);
    int first = 0;
    
    header *entete;
    champ *first_champ;
    champ *ptr_ch = first_champ;
    puts("Initialization done");
    int i = 1;
    
    while (str != NULL)
    {
        if (first == 0) {
            first = 1;
            entete = get_header(str);
            printf("str = %s\n", str);
            printf("entete = %s - %s - %s\n", entete->meth_ver, entete->uri_stat, entete->ver_msg);
            puts("Problem by print_header ?");
            print_header(entete);
            puts("No problem by print_header");
            free(str);
            ptr2 = ptr1;
            str = separate_chunks(ptr2, &ptr1);
            puts("First loop");
            continue;
        }
        if  (first == 1)
        {
            first = 2;
            first_champ = get_champ(str);
            print_champ(first_champ);
            print_champ(ptr_ch);
            free(str);
            ptr2 = ptr1;
            str = separate_chunks(ptr2, &ptr1);
            continue;
        }
        printf("Entered loop n°%d\nFirst champ = ", i);
        //print_champ(ptr_ch); puts("");
        champ *tmp = get_champ(str);
        //print_champ(tmp);
        queue_champ(&ptr_ch, tmp);
        free(str);
        ptr2 = ptr1;
        str = separate_chunks(ptr2, &ptr1);
    }
    return create_http(entete, first_champ);
}

champ *create_champ(char *entete, char *valeur) {
    champ *ptr = (champ *) calloc(1, sizeof(champ));
    ptr->entete = entete;
    ptr->valeur = valeur;
    ptr->suivant = NULL;
    return ptr;
}

champ *queue_champ (champ **ptr, champ* suiv)
{
    puts("1");
    (*ptr)->suivant = suiv;
    puts("2");
    *ptr = (*ptr)->suivant;
    puts("3");
    return *ptr;
}

header *create_header(char *meth_ver, char *uri_stat, char *ver_msg)
{
    header *ptr = (header *) calloc(1, sizeof(header));
    ptr->meth_ver = meth_ver;
    ptr->uri_stat = uri_stat;
    ptr->ver_msg = ver_msg;
    return ptr;
}

e_http *create_http (header *he, champ *ch)
{
    e_http *ptr = (e_http *) calloc(1, sizeof(e_http));
    ptr->http_header = he;
    ptr->champs = ch;
    //ptr->corps = ??;
    return ptr;
}

void print_header(header *entete)
{
    char *ent1 = hexToChar(entete->meth_ver);
    char *ent2 = hexToChar(entete->uri_stat);
    char *ent3 = hexToChar(entete->ver_msg);
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
    int i = 0;
    champ* tmp = first;
    while (tmp)
    {
        if (tmp->entete && tmp->valeur)
        {
            char *entete = hexToChar(tmp->entete);
            char *value =  hexToChar(tmp->valeur);
            printf("Champ n°%d = %s : %s\n", ++i, entete, value);
            free(entete);
            free(value);
        }
        tmp = tmp->suivant;
    }
}

void print_http(e_http *ptr)
{
    print_header(ptr->http_header);
    print_champ(ptr->champs);
    //print_corps(ptr->corps);
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
    champ *tmp;
    while(ptr)
    {
        tmp = ptr;
        ptr = ptr->suivant;
        free(tmp->entete);
        free(tmp->valeur);
        free(tmp);
    }
}

void delete_http(e_http *ptr)
{
    delete_champ(ptr->champs);
    delete_header(ptr->http_header);
    free(ptr);
}