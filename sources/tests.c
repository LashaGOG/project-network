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

void test_hexToDec_c () {
    printf("________________________________\n");
    printf("Test de la fonction HexToDec_c\n");
    char *testHexToDec[] = {"A","1","0","AB","ab","fa","f9","10   28"};     //La fonction ne gère pas les espaces, à réparer
    for (int i = 0; i < 8; i++) {
        printf("Nombre en hex : %s \n", testHexToDec[i]);
        printf("Son equivalent en decimale : %s\n", hexToDec_c(testHexToDec[i]));
    }
    printf("Test de la fonction hexToDec_c terminé\n");
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

void test_hexToChar()
{
    char *bytes =  "48 54 54 50 2f 31 2e 31 20 32 30 30 20 4f 4b 0d 0a";
    char *zebi = hexToChar(bytes);
    printf("Bytes à traduire : %s\nTraduction : %s\n", bytes, zebi);
    free(zebi);
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

void test_ipv4() {
    static int frame_counter = 1;
    char *test = "45 00 00 28 95 11 40 00 80 06 00 00 c0 a8 00 0a a2 9f 85 ea f2 47 01 bb 19 1c 70 16 62 6f 3f 36 50 10 02 02 e9 56 00 00";
    char *testpointer = &test[0];
    ipv4 *test_ipv4 = create_ipv4(testpointer, &frame_counter);
    print_ipv4(test_ipv4);
    delete_ipv4(test_ipv4);
}

void test_tcp() {
    static int frame_counter = 1; 
    char *bytes = "01 bb fd 75 db be 39 ba de 4c f6 fc 80 18 05 4a b8 89 00 00 01 01 08 0a e7 fe 1f f2 fa 38 29 8f";
    tcp *tcp_test = create_tcp(bytes,&frame_counter);
    // printf("Length total of bytes : %d\n",(int)(0.5*calculate_nb_char_hex(bytes)));
    print_tcp(tcp_test,1);
    delete_tcp(tcp_test);
}

void test_http() {
    char *bytes = "48 54 54 50 2f 31 2e 31 20 32 30 30 20 4f 4b";
    header *test = get_header(bytes);
    //printf("uristat : %s\n", test->meth_ver);
    print_header(test);
    delete_header(test);
}