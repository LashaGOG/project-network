#include "./headers/http.h"

char* separate_chunks (char *bytes) {
    char *str = strdup(bytes);
    char tmp[4] = {0};
    tmp[2] = " ";
    int i = 0, j = 1, k = 0;
    char *res = (char *) calloc(2, sizeof(char));
    
    while (str[j+3])
    {
        tmp[0] = str[i];
        tmp[1] = str[j];
        if (tmp[0] == '0' && tmp[1] == 'd') {
            tmp[0] = str[i+3];
            tmp[1] = str[j+3];
            if (tmp[0] == '0' && tmp[1] == 'a')
                continue;
            break;
        }
        else {
           res = (char *) realloc(res, (strlen(res) + 3) * sizeof(char));
           res[i] = tmp[0];
           res[j] = tmp[1];
        }
        i++;
        j++;
    }

    res = (char *) realloc(res, (strlen(res) + 1) * sizeof(char));
    res[strlen(str)] = '\0';
    free(str);

    //modify byte -> byte[j + 5] if it exists

    return res;
}

champ *get_champ (char *bytes)
{
    int i = 0, j = 1;
    while(j < (int) strlen(bytes))
    {
        if (bytes[i] == '0' && bytes[j] == '2')
        {
            char *entete = strndup(&bytes[0], (i - 1));
            char *value = strndup(&bytes[j+2], (strlen(bytes) - (j + 3)));
            break;
        }
        i++;
        j++;
    }  
    return create_champ(entete, value);
}