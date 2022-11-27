#include "./headers/tests.h"
/* on définit les tests pour chaque fonction ici */

void test_hexToBin() {
    printf("________________________________\n");
    printf("Test de la fonction hetToBin\n");
    char *testHexToBin[] = {"0","1","2","3","4","5","6","7","8","9","a","A", "B","b","C","c","D","d","E","e","F","f"}; 
    for (int i = 0; i < 22; i++) {
        printf("Nombre en Hexa : %s \n", testHexToBin[i]);
        printf("Son equivalent en binaire : ");
        hexToBin(testHexToBin[i]);
        printf("\n");  
    }
    printf("Test de la fonction hexToBin terminé\n"); 
    printf("________________________________\n");
}
void test_binToHex() {
    printf("________________________________\n");   
    printf("Test de la fonction binToHex\n");
    char *testBinToHex[] = {"0000","0001","0010","1111"}; 
    for (int i = 0; i < 4; i++) {
        printf("Nombre en bin : %s \n", testBinToHex[i]);
        printf("Son equivalent en hexa : %X\n", binToHex(testBinToHex[i]));
    }
    printf("Test de la fonction binToHex terminé\n");
    printf("________________________________\n");
}
void test_hexToDec() {
    printf("________________________________\n");
    printf("Test de la fonction HexToDec\n");
    char *testHexToDec[] = {"A","1","0","AB","ab","fa","f9","10   28"};     //La fonction ne gère pas les espaces, à réparer
    for (int i = 0; i < 8; i++) {
        printf("Nombre en hex : %s \n", testHexToDec[i]);
        printf("Son equivalent en decimale : %d\n", hexToDec(testHexToDec[i]));
    }
    printf("Test de la fonction hexToDec terminé\n");
    printf("________________________________\n");
}
void test_decToHex () {
    printf("________________________________\n");
    printf("Test de la fonction decToHex\n");
    for (int i = 0; i < 17; i++) {
        printf ("Nombre decimale : %d\n",i);
        printf ("Son equivalent en hexa : ");
        decToHex(i);
        printf("\n");
    }
    srand(time(NULL)); 
    int nb = rand() % 255 + 1 ;
    printf ("Nombre decimale : %d\n",nb);
    printf ("Son equivalent en hexa : ");
    decToHex(nb);
    printf("\n");
    printf("Test de la fonction decToHex terminé\n");
    printf("________________________________\n");
}
void test_decToBin() {
    srand(time(NULL)); 
    int nb = rand() % 255 + 1 ;
    printf ("Nombre decimale : %d\n",nb);
    printf ("Son equivalent en bin : ");
    decToBin(nb);
    printf("\n");
}
void test_binToDec(){
    printf("________________________________\n");   
    printf("Test de la fonction binToDec\n");
    char *testBinToDec[] = {"0000","0001","0010","1111"};
    for (int i = 0; i < 4; i++) {
        printf("Nombre en bin : %s \n", testBinToDec[i]);
        printf("Son equivalent en Dec : %d\n", binToDec(testBinToDec[i]));
    }
    printf("Test de la fonction binToDec terminé\n");
    printf("________________________________\n");    
}
void test_frametostr_verif()
{
    FILE *fd = fopen("test2.txt", "w");
    fclose(fd);
    fd = fopen("test3.txt", "w");
    fclose(fd);
    frametostr("format.txt", "test2.txt");
    verif("test2.txt", "test3.txt");
}
/* ETHERNET.C */

void test_get_mac_address() {
    static int frame_counter = 1; 
    char testBytes[1000];
    FILE *fd;
    if ((fd = fopen("test3.txt", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    // reads text until newline is encountered
    fscanf(fd, "%[^\n]", testBytes);
    char* testpointer = &testBytes[0];                                     //on devrait utiliser un pointer pour faciliter le parcours
    eth_frame *test_frame = create_eth_frame(testpointer,&frame_counter);
    print_eth_frame(test_frame);
    delete_eth_frame(test_frame);
    fclose(fd);
}

void test_hexToBinchar() {
    char *test = "ae 74";
    char *res = hexToBinchar(test);
    printf("hextobinchar : %s\n", res);
    free(res);
}