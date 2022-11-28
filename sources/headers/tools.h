#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#ifndef TOOLS 
#define TOOLS

char *intToStr (int n);
void hexToBin(char *hex);
char *hexToBinchar(char *hex);
unsigned char binToHex (char *bin);
int hexToDec (char *hex);
char *hexToDec_c (char *hex);
void decToHex (int dec);
void decToBin(int n);
int binToDec(char *bin);

void change_separator_str (char *str, const char old_separator, const char new_separator);

void remove_spaces (char* restrict str_trimmed, const char* restrict str_untrimmed);

#endif // TOOLS