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
    int lenght = strlen(hex);
    for (int i = 0; i < lenght; i++) {
        char digit = hex[lenght - 1 - i]; 

        if (digit >= '0' && digit <= '9') {
            nbdec += (digit - '0') * pow(16,i); 
        }
        else if  ((digit >= 'a' && digit <= 'f')){
            nbdec += (digit - 'a' + 10) * pow(16,i); 
        }
        else {
            nbdec += (digit - 'A' + 10) * pow(16,i); 
        }
    }
    return nbdec; 
}

