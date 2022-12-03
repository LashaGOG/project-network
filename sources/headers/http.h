#include "tools.h"

#ifndef _HTTP
#define _HTTP

typedef struct _champ{
    char *entete;
    char *valeur;
    struct _champ *suivant;
} champ;

typedef struct _header{
    char *meth_ver;
    char *uri_stat;
    char *ver_msg;
} header;

typedef struct entete_http {
    struct _header *http_header;
    struct _champ *champs;
    char *corps;
} e_http;

char *separate_chunks (char *bytes);
champ *get_champ (char *bytes);
header *get_header (char *bytes);

champ *create_champ(char *entete, char *valeur);
champ *queue_champ (champ **ptr, champ* suiv);
header *create_header(char *meth_ver, char *url_stat, char *ver_msg);
e_http *create_http (header *he, champ *ch);

champ *queue_champ (champ **ptr, champ* suiv);
void print_header(header *entete);
void print_champ(champ *first);
void print_http(e_http *ptr);

void delete_header(header *ptr);
void delete_champ(champ *ptr);
void delete_http(e_http *ptr);

#endif //_HTTP