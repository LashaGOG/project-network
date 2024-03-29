#include "./headers/reader.h"

void mem_reset(char* buff, size_t n)
{
    for (size_t i = 0; i < n; i++)
        buff[i] = '\0';
}

void writedown(char* str, char* nomfic)
{
    FILE* fd = fopen(nomfic, "a");
    if (!fd)
    {
        puts("Failed to open file (reader.c, writedown).");
        return;
    }
    fprintf(fd, "%s\n", str);
    fclose(fd);
}

void frametostr (char* nomfic, char* save)
{
    FILE* fd = fopen(nomfic, "r");
    if (!fd)
    {
        puts("Faild to open file (reader.c, frametostr).");
        return;
    }
    char ligne[256] = {0};
    char* buff = ligne;
    char* prefix = "0000";
    char* str = calloc(3500, sizeof(char));
    int i = 0, n = 47, pos = 7, k;
    size_t len = 256;

    while (getline(&buff, &len, fd) != -1)
    {
        //printf("buff : %s", buff);
        if (strncmp(prefix, buff, strlen(prefix)) == 0)
        {
            if (str[0] != '\0')
            {
                writedown(str, save);
                mem_reset(str, 3500);
                i = 0;
            }
        }

        n = 47; k = 0;
        while (k < n)
        {
            if ((buff[k + pos] == ' ') && (buff[k + pos + 1] == ' '))
            {
                break;
            }
            str[i] = buff[k + pos];
            k++;
            i++;
        }
        str[i++] = ' ';
        mem_reset(buff, len);
    }
    writedown(str, save); 

    free(str);
    fclose(fd);
}

void verif (char* nomfic, char* save)
{
    FILE* fd = fopen(nomfic, "r");
    if (!fd)
    {
         puts("Failed to open file (reader.c, verif).");
        return;
    }
    
    char* ligne = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0, k, nbtrame = 0;
    
    while ((read = getline(&ligne, &len, fd)) != -1)
    {
        nbtrame++;
        k = 1;
        for  (i = 0; i < (int)strlen(ligne); i++)
        {
            if (k == 0) break;
            if (isxdigit(ligne[i]) == 0)
            {
                if (ligne[i] != ' ' && ligne[i] != '\n' && ligne[i] != '\0')
                {
                    k = 0;
                    printf("Frame n %d ignored, a non hexadecimal character has been found.\n", nbtrame);
                }
            }
        }
        if (k == 1)
        {
            ligne[strlen(ligne)] = '\0';
            ligne[strlen(ligne) - 1] = '\0';
            writedown(ligne, save);
        }
        mem_reset(ligne, strlen(ligne));
    }
    free(ligne);
    fclose(fd);
}