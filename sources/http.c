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
    int i = 0, j = 1, k = 0;
    int pos = 0;
    char *meth_ver;
    char *uri_stat;
    char *ver_msg;
    while (j < (int) strlen(bytes))
    {
        if (bytes[i] == '0' && bytes[j] == '2')
        {
            if (k == 0) {
                meth_ver = strndup(&bytes[0], (i - 1));
                pos = j+2;
                k++;
            }
                
            if (k == 1) {
                uri_stat = strndup(&bytes[pos], (i - 1));
                ver_msg = strndup(&bytes[j+2], (strlen(bytes) - (j + 3)));
                break;
            }
        }
        i++;
        j++;
    }
    header *ptr = create_header(meth_ver, uri_stat, ver_msg);
    free(meth_ver);
    free(uri_stat);
    free(ver_msg);
    return ptr;
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
    char *ent1 = hextochar(entete->meth_ver);
    char *ent2 = hextochar(entete->uri_stat);
    char *ent3 = hextochar(entete->ver_msg);
    if (strcmp("HTTP", ent1) == 0)
    {
        printf("Response Version : %s\nStatus code : %s\n, Response Phrase : %s\n", ent1, ent2, ent3);
    }
    else
    {
        printf("Request Method : %s\nRequest URI : %s\nRequest Version : %s\n", ent1, ent2, ent3);
    }
}

void print_champ(champ *first)
{
    int i = 0;
    champ* tmp;
    while (tmp)
    {
        if (tmp->entete && tmp->valeur)
        {
            printf("Champ n°%d :\n-%s\n-%s\n\n", ++i, hextochar(tmp->entete), hextochar(tmp->valeur));
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