#include "./headers/http.h"

char* separate_chunks (char *bytes) {
    char *str = strdup(bytes);
    char tmp[4] = {0};
    tmp[2] = ' ';
    int i = 0, j = 1, k = 0;
    char *res = (char *) calloc(strlen(bytes), sizeof(char));
    
    while (str[j+3])
    {
        tmp[0] = str[i];
        tmp[1] = str[j];
        if (tmp[0] == '0' && tmp[1] == 'd') {
            tmp[0] = str[i+3];
            tmp[1] = str[j+3];
            if (tmp[0] == '0' && tmp[1] == 'a')
            {
                if (i == 0  && j == 1)
                {
                    k = 1;
                }
                break;
            }
        }
        else {
           res[i] = tmp[0];
           res[j] = tmp[1];
        }
        i++;
        j++;
    }

    if (k == 0)
    {
        res = (char *) realloc(res, (strlen(res) + 1) * sizeof(char));
        res[strlen(str)] = '\0';
        if  (j + 5 < (int) strlen(bytes))
        {
            bytes = &bytes[j + 5];
        }
        else {
            bytes = &bytes[strlen(bytes) - 1];
        }
    }
    else
    {
        free(res);
        free(str);
        return NULL;
    }

    free(str);
    //if (j + 5 > strlen()
    //modify byte -> byte[j + 5] if it exists

    return res;
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

                ver_msg = calloc(strlen(bytes) - (j + 1), sizeof(char));
                strncpy(ver_msg, &bytes[j+2], (strlen(bytes) - (j + 2)));
                break;
            }
            if (k == 0) {
                meth_ver = (char  *) calloc(i, sizeof(char));
                strncpy(meth_ver, &bytes[0], (i - 1));
                pos = j+2;
                k++;
            }
        }
        i++;
        j++;
    }
    //header *ptr = create_header(meth_ver, uri_stat, ver_msg);
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