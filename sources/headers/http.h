#include "tools.h"

#ifndef _HTTP
#define _HTTP

typedef struct _champ{
    char *entete;
    char *valeur;
    struct _champ *suivant;
} champ;

typedef struct entete_http {
    int num_trame;
    char *meth_ver;
    char *url_stat;
    char *ver_msg;
    champ *champs;
    char *corps;
} e_http;

char *isolate(char *bytes, char *separator);
champ *get_champ(char *bytes);


#endif //_HTTP