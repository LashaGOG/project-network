#include "./headers/tools.h"

char *intToStr (int n) {
    /* cast n to str */
    int len = sizeof(int)*8+1; 
    char* nb = (char*) calloc (len, sizeof(char)); 
    snprintf(nb, len, "%d", n);
    // sprintf(nb, n);
    return nb; 
}

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
    char *str = spaceless(hex);
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        char digit = str[length - 1 - i]; 

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

char *spaceless(char* str)
{
    // Initialize a counter variable to store the new string length
    int count = 0;

    // Iterate over the input string and copy each non-space character to the
    // new string
    for (int i = 0; i < (int)strlen(str); i++) {
        if (str[i] != ' ') {
            str[count] = str[i];
            count++;
        }
    }

    // Terminate the new string with a null character
    str[count] = '\0';
    return str;
}

unsigned long hexToUnsLong (char *hex) {
    /* convertir nb hexadecimale au nb decimale */
    unsigned long nbdec = 0 ; 
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

char *hexToDec_c (char *hex) {
    /* return value of hex as decimal, casted to string */
    return intToStr(hexToDec(hex));
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

//char *hexToChar(char *bytes)
//{
//    char *doublon = strdup(bytes);
//    char *first = doublon;
//    int i = 0, len = strlen(bytes), k = 0;
//    int res[len];
//    char* ptr = strtok(doublon, ". ");
//    while (ptr)
//    {
//        res[i] = hexToDec(ptr);
//        //printf("ptr : '%s' => res[%d] = %d\n", ptr, i, res[i]);
//        i++;
//        ptr = strtok(NULL,". ");
//    }
//
//    k = i + 1;
//    char *str = (char *) calloc(k, sizeof(char));
//    i = 0;
//    while (res[i])
//    {
//        if (res[i])
//        {
//            str[i] = res[i];
//        }
//        else{
//            break;
//        }
//        i++;
//    }
//
//    free(first);
//    return str;
//}

char *hexToChar(char *bytes)
{
    char *res = calloc(strlen(bytes), sizeof(char));
    char *str = strndup(&bytes[0], strlen(bytes));
    char *first = str;
    
    const char *separators = " ";
    char *tok = strtok(str, separators); //replaces all separators to '\0'

    char *tmp = (char *) calloc(2,sizeof(char));
    long a;
    
    while(tok)              //BIG PROBLEMS WITH HEXTOCHAR WTF CRASHES RIGHT HERE (SEGFAULT)
    {   
        a = strtol(tok, 0, 16);          //convert characters to long (base 16)
        sprintf(tmp, "%c", (int) a);     //convert long to ascii
        strcat(res, tmp);                //concatenate in res
        mem_reset(tmp, (size_t) 2);
        tok = strtok(NULL, separators);  //tok retrieves pointer of char right after next  separator
    }
    
    free(first);
    free(tmp);
    res = (char*) realloc(res, (strlen(res) + 1) * sizeof(char));
    return res;   
}


int word_count(char *s)
{
    int count;
    for (int i = 0; s[i+1] != '\0'; i++)
    {
        if (s[i] == ' ' && s[i+1] != ' ')
            count++;    
    }
    return count;
}

int calculate_nb_char_hex (char *bytes){
    /* returns nb of hexadecimal characters in bytes. */
    /* this fonction will allow us to calculate nb of bits/bytes */
    int length = strlen(bytes);
    int nb_separators = 0; 

    for (int i = 0; bytes[i]!='\0'; i++) {
        if (bytes[i]== ' ') nb_separators++; 
    }
    return (int)((length-nb_separators)); 
}

char *hex_to_ip(const char *hex_ip) {
    char *ip = (char *) calloc(strlen(hex_ip) + 5, sizeof(char));
    int i = 0, k = 0;

    if (ip == NULL)
        return NULL;
    
    if (hex_ip == NULL)
        return NULL;
    
    for (i = 0; i < (int) strlen(hex_ip); i += 3) {
        if (hex_ip[i] == '.') {
           ip[k++] = '.';
           continue;
        }
       
        char hex_chars[3] = {hex_ip[i], hex_ip[i + 1], '\0'};
        
        int dec = hexToDec(hex_chars);
        int len_dec = snprintf(NULL, 0, "%d", dec); 
        
        sprintf(&(ip[k]), "%d", dec);
        k += len_dec; 
        
        if (i < (int) strlen(hex_ip) - 3)
            ip[k++] = '.';
    }
    ip[k] = '\0';
    return ip;
}