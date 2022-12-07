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

char *separate_chunks(char *bytes, char **ptr);
champ *get_champ (char *bytes);
header *get_header (char *bytes);
e_http *get_http(char *bytes);
char *get_corps(char *bytes);

champ *create_champ(char *entete, char *valeur);
champ *queue_champ (champ **ptr, champ* suiv);
header *create_header(char *meth_ver, char *url_stat, char *ver_msg);
e_http *create_http (header *he, champ *ch, char *corps);

champ *queue_champ (champ **ptr, champ* suiv);
void print_header(header *entete);
void print_champ(champ *first);
void print_http(e_http *ptr);

void delete_header(header *ptr);
void delete_champ(champ *ptr);
void delete_http(e_http *ptr);

void fprint_header(FILE *fd, header *entete);
void fprint_champ(FILE *fd, champ *first);
void fprint_http(FILE *fd,  e_http *ptr);

#endif //_HTTP