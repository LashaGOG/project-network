#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef READER_H
#define READER_H

void mem_reset(char* buff, size_t n);
void writedown(char* str, char* nomfic);
void frametostr(char* nomfic, char* save);

#endif