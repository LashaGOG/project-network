#include "./headers/http.h"

char* separate_chunks (char *bytes) {
    char *str = strdup(bytes);
    char tmp[4] = {0};
    tmp[2] = ' ';
    int i = 0, j = 1;
    char *res = (char *) calloc(2, sizeof(char));
    
    while (str[j+3])
    {
        tmp[0] = str[i];
        tmp[1] = str[j];
        if (tmp[0] == '0' && tmp[1] == 'd') {
            tmp[0] = str[i+3];
            tmp[1] = str[j+3];
            if (tmp[0] == '0' && tmp[1] == 'a')
                continue;
            break;
        }
        else {
           res = (char *) realloc(res, (strlen(res) + 3) * sizeof(char));
           res[i] = tmp[0];
           res[j] = tmp[1];
        }
        i++;
        j++;
    }

    res = (char *) realloc(res, (strlen(res) + 1) * sizeof(char));
    res[strlen(str)] = '\0';
    free(str);

    //modify byte -> byte[j + 5] if it exists

    return res;
}

champ *get_champ (char *bytes) {
    int i = 0, j = 1;
    char *entete;
    char *value;
    while(j < (int) strlen(bytes))
    {
        if (bytes[i] == '0' && bytes[j] == '2')
        {
            entete = strndup(&bytes[0], (i - 1));
            value = strndup(&bytes[j+2], (strlen(bytes) - (j + 3)));
            break;
        }
        i++;
        j++;
    }  
    return create_champ(entete, value);
}

header *get_header (char *bytes) {
    printf("bytes : %s\n", bytes);
    int i = 0, j = 1, k = 0;
    int pos = 0;
    char *mv;
    char *us;
    char *vm;

    while (j < (int) strlen(bytes))
    {
        if (bytes[i] == '2' && bytes[j] == '0')
        {               
            if (k == 1) {
                char uri_stat[i - pos];
                uri_stat[i - pos - 1] = '\0';
                strncpy(uri_stat, &bytes[pos], (i - pos - 1));
                us = &uri_stat[0];
                printf("uv = %s\n", us);
                
                char ver_msg[strlen(bytes) - (j + 1)];
                strncpy(ver_msg, &bytes[j+2], (strlen(bytes) - (j + 2)));
                ver_msg[strlen(bytes) - (j + 1) - 1] = '\0';
                vm = &ver_msg[0];
                printf("vm = %s\n", vm);
                //printf("meth_ver : %s\nuri_stat : %s\nver_msg : %s\n", meth_ver, uri_stat, ver_msg);
                break;
            }
            if (k == 0) {
                char meth_ver[i];
                strncpy(meth_ver, &bytes[0], (i - 1));
                meth_ver[i - 1] = '\0';
                mv = &meth_ver[0];
                printf("mv = %s\n", mv);
                pos = j+2;
                k++;
            }
        }
        i++;
        j++;
    }
    //header *ptr = create_header(meth_ver, uri_stat, ver_msg);
    return create_header(mv, us, vm);
}

champ *create_champ(char *entete, char *valeur) {
    champ *ptr = (champ *) calloc(1, sizeof(champ));
    ptr->entete = entete;
    ptr->valeur = valeur;
    ptr->suivant = NULL;
    return ptr;
}

//champ *queue_champ (champ **ptr, champ* suiv)
//{
    //&ptr ou *ptr ou ptr->suiv new;
    //&ptr ou *ptr ou ptr = ptr->suiv;
    //return &ptr;
//}

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
            printf("Champ n°%d :\n-%s\n-%s\n\n", ++i, entete, value);
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