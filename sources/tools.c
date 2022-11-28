#include "./headers/tools.h"

void hexToBin(char *hex) {
    /* Convertir nombre hexadecimale au nombre Binaire */
    int i = 0; 
    while (hex[i]) {
        switch (hex[i])
        {
        case '0':
            printf("0000");
            break;
        case '1':
            printf("0001");
            break;
        case '2':
            printf("0010");
            break;
        case '3':
            printf("0011");
            break;
        case '4':
            printf("0100");
            break;
        case '5':
            printf("0101");
            break;
        case '6':
            printf("0110");
            break;
        case '7':
            printf("0111");
            break;
        case '8':
            printf("1000");
            break;
        case '9':
            printf("1001");
            break;
        case 'A':
            printf("1010");
            break;
        case 'a':
            printf("1010");
            break;
        case 'B':
            printf("1011");
            break;
        case 'b':
            printf("1011");
            break;
        case 'C':
            printf("1100");
            break;
        case 'c':
            printf("1100");
            break;
        case 'D':
            printf("1101");
            break;
        case 'd':
            printf("1101");
            break;
        case 'E':
            printf("1110");
            break;
        case 'e':
            printf("1110");
            break;
        case 'F':
            printf("1111");
            break;
        case 'f':
            printf("1111");
            break;
        default:
            printf("Invalid input for Hex\n"); 
            break;
        }
        i++; 
    }
}

int lenhex (char *hex){
    int i = 0, len = 0;
    while (hex[i]) {
        if (isxdigit(hex[i]) > 0)
            len++;
        i++;
    }
    return len;
}

char* hexToBinchar(char *hex) {
    /* Convertir nombre hexadecimale au nombre Binaire */
    int i = 0;
    int len = lenhex(hex) * 4 + 1;
    char *res = (char *) calloc(len, sizeof(char));
    char *temp; 
    while (hex[i]) {
        switch (hex[i])
        {
        case '0':
            temp = "0000";
            break;
        case '1':
            temp = "0001";
            break;
        case '2':
            temp = "0010";
            break;
        case '3':
            temp = "0011";
            break;
        case '4':
            temp = "0100";
            break;
        case '5':
            temp = "0101";
            break;
        case '6':
            temp = "0110";
            break;
        case '7':
            temp = "0111";
            break;
        case '8':
            temp = "1000";
            break;
        case '9':
            temp = "1001";
            break;
        case 'A':
            temp = "1010";
            break;
        case 'a':
            temp = "1010";
            break;
        case 'B':
            temp = "1011";
            break;
        case 'b':
            temp = "1011";
            break;
        case 'C':
            temp = "1100";
            break;
        case 'c':
            temp = "1100";
            break;
        case 'D':
            temp = "1101";
            break;
        case 'd':
            temp = "1101";
            break;
        case 'E':
            temp = "1110";
            break;
        case 'e':
            temp = "1110";
            break;
        case 'F':
            temp = "1111";
            break;
        case 'f':
            temp = "1111";
            break;
        default:
            temp = "";
            if (hex[i] == '\0')
                printf("Invalid input for Hex\n"); 
            break;
        }
        strcat(res, temp);
        i++; 
    }
    return res;
}

unsigned char binToHex (char *bin) {
    /* Convertir nombre binaire au nombre hexadecimale */
    char *a = bin;
    unsigned char num = 0;
    do {
        int b = *a=='1'?1:0;
        num = (num<<1)|b;
        a++;
    } while (*a);
    return num ; 
}

int hexToDec (char *hex) {
    /* convertir nb hexadecimale au nb decimale */
    int nbdec = 0 ; 
    int length = strlen(hex);
    for (int i = 0; i < length; i++) {
        char digit = hex[length - 1 - i]; 

        if (digit >= '0' && digit <= '9') {
            nbdec += (digit - '0') * pow(16,i); 
        }
        else if  ((digit >= 'a' && digit <= 'f')){
            nbdec += (digit - 'a' + 10) * pow(16,i); 
        }
        else if ((digit >= 'A' && digit <= 'F')){
            nbdec += (digit - 'A' + 10) * pow(16,i); 
        }
    }
    return nbdec; 
}

void decToHex (int dec) {
    /* convertir nb decimale en hexa */
    char hexTemp[20] ; // Taille 20 ? 
    int i = 0 ; 
    while (dec != 0) {
        int temp = 0 ; 

        temp = dec % 16 ; 

        if (temp < 10) {
            hexTemp[i++] = 48 + temp ;  
        }
        else {
            hexTemp[i++] = 55 + temp ; 
        }
        dec /= 16 ; 
    }
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%c",hexTemp[j]);
    }
    return ;
}

void decToBin(int n) {
    /* convertir de decimale vers binaire */
    int bin[32];
    int i = 0;
    while (n > 0) {
        bin[i] = n % 2;
        n = n / 2;
        i++;
    }
  
    for (int j = i - 1; j >= 0; j--)
        printf("%d", bin[j]);
}

int binToDec(char *bin) {
    /* convertir de binaire vers decimale */
    int dec = 0; 
    int puiss = strlen(bin) - 1; 
    int i = 0; 
    while (bin[i]) {
        int dig = (int)(bin[i]) - (int)('0');
        dec += dig * pow(2,puiss); 
        i++;
        puiss --; 
    }
    return dec; 
}

void change_separator_str (char *str, const char old_separator, const char new_separator) {
    /* change separator in string */
    int length = strlen(str); 
    for (int i = 0; i < length; i++) {
        if (str[i] == old_separator) str[i] = new_separator;
    }
}

void remove_spaces (char* restrict str_trimmed, const char* restrict str_untrimmed)
{
  while (*str_untrimmed != '\0')
  {
    if(!isspace(*str_untrimmed))
    {
      *str_trimmed = *str_untrimmed;
      str_trimmed++;
    }
    str_untrimmed++;
  }
  *str_trimmed = '\0';
}