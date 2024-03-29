// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
#include <math.h>
// #include <ctype.h>
// #include <time.h>
// #include <unistd.h> 
#include <strings.h>
#include <wchar.h>
//#include <regex.h>
#include <stdbool.h>
#include "reader.h"

#ifndef TOOLS 
#define TOOLS

char *intToStr (int n);
char *unsLongToStr (unsigned long n);
void hexToBin(char *hex);
char *hexToBinchar(char *hex);
unsigned char binToHex (char *bin);
int hexToDec (char *hex);
unsigned long hexToUnsLong (char *hex);
char *hexToDec_c (char *hex);
void decToHex (int dec);
void decToBin(int n);
int binToDec(char *bin);
char *hexToChar(char *bytes);
int word_count(char *s);
char *hex_to_ip(const  char *hex_ip);
char *spaceless(char* str);

void change_separator_str (char *str, const char old_separator, const char new_separator);

void remove_spaces (char* restrict str_trimmed, const char* restrict str_untrimmed);
int calculate_nb_char_hex (char *bytes);

char* h_strndup(const char*  s, size_t n);


#endif // TOOLS