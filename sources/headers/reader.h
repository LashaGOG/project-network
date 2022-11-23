#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#ifndef READER_H
#define READER_H

void mem_reset(char* buff, size_t n);
void writedown(char* str, char* nomfic);
void frametostr(char* nomfic, char* save);
void verif (char* nomfic, char* save);

#endif //READER_H