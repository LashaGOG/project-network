#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef TOOLS 
#define TOOLS

void hexToBin(char *hex); 
unsigned char binToHex (char *bin);
int hexToDec (char *hex);
void decToHex (int dec);
void decToBin(int n);
int binToDec(char *bin);

void change_separator_str (char *str, const char old_separator, const char new_separator);

#endif // TOOLS