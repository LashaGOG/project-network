#include "./headers/http.h"

char* separate_chunks (char *bytes) {
    char *str = strdup(bytes);
    char tmp[4] = {0};
    tmp[2] = " ";
    int i = 0, j = 1;
    char *res = (char *) calloc(2, sizeof(char));
    
    while (str[j+3])
    {
        tmp[0] = str[i];
        tmp[1] = str[j];
        i += 3;
        j += 3;
        if (tmp[0] == '0' && tmp[1] == 'd') {
            tmp[0] = str[i];
            tmp[1] = str[j];
            if (tmp[0] == '0' && tmp[1] == 'a')
                continue;
            bytes = bytes[j+3];
        }
        else {
           res = (char *) realloc(res, (strlen(res) + 4) * sizeof(char));
           res[i] = tmp[0];
           res[j] = tmp[1];
           res[j + 1] = tmp[2];
        }

    }


    free(str);
    return char*
}
