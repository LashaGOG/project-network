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

void test_hex_to_ip()
{
    char *addr = "a2.9f.87.ea";
    char *ip = hex_to_ip(addr);
    printf("%s => %s\n", addr, ip);
    free(ip);
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
    eth_frame *test_frame = create_eth_frame(testpointer, frame_counter);
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
    ipv4 *test_ipv4 = create_ipv4(testpointer, frame_counter);
    print_ipv4(test_ipv4);
    delete_ipv4(test_ipv4);
}

void test_tcp() {
    static int frame_counter = 1; 
    char *bytes = "01 bb fd 75 db be 39 ba de 4c f6 fc 80 18 05 4a b8 89 00 00 01 01 08 0a e7 fe 1f f2 fa 38 29 8f";
    tcp *tcp_test = create_tcp(bytes, frame_counter);
    // printf("Length total of bytes : %d\n",(int)(0.5*calculate_nb_char_hex(bytes)));
    print_tcp(tcp_test,1);
    delete_tcp(tcp_test);
}

void test_http() {
    /* Test serarate_chunks */
    puts("____Test separate____");
    char *chunks = "58 2d 46 65 64 6f 72 61 2d 52 65 71 75 65 73 74 49 44 3a 20 59 34 43 51 4e 5f 34 73 41 72 43 57 56 37 76 68 30 61 32 57 33 51 41 41 44 5a 67 0d 0a 43 6f 6e 74 65 6e 74 2d 54 79 70 65 3a 20 74 65 78 74 2f 70 6c 61 69 6e 0d 0a 0d 0a";
    char *ptr = chunks; // don't forget to initialize
    printf("avant separate ptr = %s\n", ptr);
    char *strchunk = separate_chunks(chunks, &ptr); // adress of pointer on argument
    printf("apres separate ptr = %s\n", ptr);
    printf("strchunk = %s\n", strchunk);
    char *end = "0d 0a";
    ptr = end;
    char *strchunk2 = separate_chunks(end,&ptr);
    printf("strchunk2 = %s\n", strchunk2);


    free(strchunk);
    if (strchunk2 != NULL)
        free(strchunk2);

    /* Test header */
    puts("____Test header____");
    char *bytes = "48 54 54 50 2f 31 2e 31 20 32 30 30 20 4f 4b";
    header *test = get_header(bytes);
    print_header(test);

    /* Test champ */
    puts("____Test champ____");
    char *bytes3 = "58 2d 46 65 64 6f 72 61 2d 52 65 71 75 65 73 74 49 44 3a 20 59 34 43 51 4e 5f 34 73 41 72 43 57 56 37 76 68 30 61 32 57 33 51 41 41 44 5a 67";
    char *bytes2 = "58 2d 46 65 64 6f 72 61 2d 50 72 6f 78 79 53 65 72 76 65 72 3a 20 70 72 6f 78 79 30 31 2e 69 61 64 32 2e 66 65 64 6f 72 61 70 72 6f 6a 65 63 74 2e 6f 72 67";
    champ *test2  = get_champ(bytes2);
    champ *test3  = get_champ(bytes3);
    test2->suivant = test3;
    print_champ(test2);

    /* Test http */
    puts("____Test http____");
    //e_http *http = create_http(test, test2);

    //delete_header(test);
    //delete_champ(test2);
    //print_http(http);
    //delete_http(http);
}

void test_get_http()
{
    char *bytes = "48 54 54 50 2f 31 2e 31 20 32 30 30 20 4f 4b 0d 0a 44 61 74 65 3a 20 46 72 69 2c 20 32 35 20 4e 6f 76 20 32 30 32 32 20 30 39 3a 35 31 3a 35 31 20 47 4d 54 0d 0a 53 65 72 76 65 72 3a 20 41 70 61 63 68 65 0d 0a 55 70 67 72 61 64 65 3a 20 68 32 0d 0a 43 6f 6e 6e 65 63 74 69 6f 6e 3a 20 55 70 67 72 61 64 65 2c 20 63 6c 6f 73 65 0d 0a 4c 61 73 74 2d 4d 6f 64 69 66 69 65 64 3a 20 57 65 64 2c 20 31 33 20 4d 61 79 20 32 30 32 30 20 32 30 3a 31 33 3a 33 35 20 47 4d 54 0d 0a 41 63 63 65 70 74 2d 52 61 6e 67 65 73 3a 20 62 79 74 65 73 0d 0a 43 6f 6e 74 65 6e 74 2d 4c 65 6e 67 74 68 3a 20 32 0d 0a 43 61 63 68 65 2d 43 6f 6e 74 72 6f 6c 3a 20 6d 75 73 74 2d 72 65 76 61 6c 69 64 61 74 65 0d 0a 45 78 70 69 72 65 73 3a 20 46 72 69 2c 20 32 35 20 4e 6f 76 20 32 30 32 32 20 30 39 3a 35 31 3a 35 31 20 47 4d 54 0d 0a 41 70 70 54 69 6d 65 3a 20 44 3d 38 33 0d 0a 58 2d 46 65 64 6f 72 61 2d 50 72 6f 78 79 53 65 72 76 65 72 3a 20 70 72 6f 78 79 30 31 2e 69 61 64 32 2e 66 65 64 6f 72 61 70 72 6f 6a 65 63 74 2e 6f 72 67 0d 0a 58 2d 46 65 64 6f 72 61 2d 52 65 71 75 65 73 74 49 44 3a 20 59 34 43 51 4e 5f 34 73 41 72 43 57 56 37 76 68 30 61 32 57 33 51 41 41 44 5a 67 0d 0a 43 6f 6e 74 65 6e 74 2d 54 79 70 65 3a 20 74 65 78 74 2f 70 6c 61 69 6e 0d 0a 0d 0a";
    e_http *http_frame = get_http(bytes);
    print_http(http_frame);
    delete_http(http_frame);
}

void test_flow_graph() {
    static int frame_counter = 10;
    char *bytes = "f0 18 98 54 9e 14 16 87 6a b7 3e 64 08 00 45 50 00 34 00 00 00 00 3d 06 9c d4 a2 9f 87 ea ac 14 0a 02 01 bb dd b5 fe 7b e2 97 44 c6 dc 93 80 10 00 31 c7 77 00 00 01 01 08 0a d8 34 b6 43 2e 25 2f f8";
    print_heading_row();
    // print_comm(bytes,&frame_counter);

    // char *header = "48 54 54 50 2f 31 2e 31 20 32 30 30 20 4f 4b";
    // struct _header *test = get_header(header);
    
    // char *bytes3 = "58 2d 46 65 64 6f 72 61 2d 52 65 71 75 65 73 74 49 44 3a 20 59 34 43 51 4e 5f 34 73 41 72 43 57 56 37 76 68 30 61 32 57 33 51 41 41 44 5a 67";
    // char *bytes2 = "58 2d 46 65 64 6f 72 61 2d 50 72 6f 78 79 53 65 72 76 65 72 3a 20 70 72 6f 78 79 30 31 2e 69 61 64 32 2e 66 65 64 6f 72 61 70 72 6f 6a 65 63 74 2e 6f 72 67";
    // champ *test2  = get_champ(bytes2);
    // champ *test3  = get_champ(bytes3);
    // test2->suivant = test3;
    
    // e_http *http_frame = create_http(test, test2);

    
    // char *bytes4 = "01 bb fd 75 db be 39 ba de 4c f6 fc 80 18 05 4a b8 89 00 00 01 01 08 0a e7 fe 1f f2 fa 38 29 8f";

    // tcp *tcp_test = create_tcp(bytes4,  frame_counter);
    // char *ipv4_frame = "45 00 00 28 95 11 40 00 80 06 00 00 c0 a8 00 0a a2 9f 85 ea f2 47 01 bb 19 1c 70 16 62 6f 3f 36 50 10 02 02 e9 56 00 00";
    // ipv4 *ip_frame = create_ipv4(ipv4_frame, frame_counter);

    // print_tcp_fg(tcp_test);
    // // print_http_fg(tcp_test, http_frame);
    // print_ipv4_fg(ip_frame);
    
    // delete_ipv4(ip_frame);



    // print_http_fg(tcp_test, http_frame);  

    // delete_http(http_frame);
    eth_frame *eFrame = create_eth_frame(bytes,frame_counter);
    print_flow(eFrame);
    delete_eth_frame(eFrame);
    // delete_tcp(tcp_test);
    
}   

/* TEST DE FRAME.C */
void test_frame()
{
    static int frame_counter = 0;
    char  *bytes = "c8 09 a8 da 3c ac 44 a6 1e 3f 48 91 08 00 45 00 01 ca d7 9f 40 00 35 06 48 2f 26 91 3c 14 c0 a8 01 12 00 50 f5 d1 2a c6 e6 b7 ee 53 42 9a 50 18 01 f6 95 f0 00 00 48 54 54 50 2f 31 2e 31 20 32 30 30 20 4f 4b 0d 0a 44 61 74 65 3a 20 46 72 69 2c 20 32 35 20 4e 6f 76 20 32 30 32 32 20 30 39 3a 35 31 3a 35 31 20 47 4d 54 0d 0a 53 65 72 76 65 72 3a 20 41 70 61 63 68 65 0d 0a 55 70 67 72 61 64 65 3a 20 68 32 0d 0a 43 6f 6e 6e 65 63 74 69 6f 6e 3a 20 55 70 67 72 61 64 65 2c 20 63 6c 6f 73 65 0d 0a 4c 61 73 74 2d 4d 6f 64 69 66 69 65 64 3a 20 57 65 64 2c 20 31 33 20 4d 61 79 20 32 30 32 30 20 32 30 3a 31 33 3a 33 35 20 47 4d 54 0d 0a 41 63 63 65 70 74 2d 52 61 6e 67 65 73 3a 20 62 79 74 65 73 0d 0a 43 6f 6e 74 65 6e 74 2d 4c 65 6e 67 74 68 3a 20 32 0d 0a 43 61 63 68 65 2d 43 6f 6e 74 72 6f 6c 3a 20 6d 75 73 74 2d 72 65 76 61 6c 69 64 61 74 65 0d 0a 45 78 70 69 72 65 73 3a 20 46 72 69 2c 20 32 35 20 4e 6f 76 20 32 30 32 32 20 30 39 3a 35 31 3a 35 31 20 47 4d 54 0d 0a 41 70 70 54 69 6d 65 3a 20 44 3d 38 33 0d 0a 58 2d 46 65 64 6f 72 61 2d 50 72 6f 78 79 53 65 72 76 65 72 3a 20 70 72 6f 78 79 30 31 2e 69 61 64 32 2e 66 65 64 6f 72 61 70 72 6f 6a 65 63 74 2e 6f 72 67 0d 0a 58 2d 46 65 64 6f 72 61 2d 52 65 71 75 65 73 74 49 44 3a 20 59 34 43 51 4e 5f 34 73 41 72 43 57 56 37 76 68 30 61 32 57 33 51 41 41 44 5a 67 0d 0a 43 6f 6e 74 65 6e 74 2d 54 79 70 65 3a 20 74 65 78 74 2f 70 6c 61 69 6e 0d 0a 0d 0a 4f 4b";
    frame *fr = create_frame(bytes, &frame_counter);
    fr->print = 1;
    print_frame(fr);
    delete_frame(fr);
}


/*Function to add in main :


Open file
Verify if file opened correctly

char* buffer 
size_t len
ssize_t read

while((read = getline(&buffer, &len, fd)) != -1)
{

    creates ethernet frame from getline(bytes)
    if protocol = 0x0800
        create ipv4 frame from ethernet payload
        if create_ipv4 returns NULL pointer OR length does not match announced length
            abort creation of ipv4 frame
            free(ethernet)
            new getline
            continue
        if protocol = 0x06
            create tcp frame from ipv4 payload
            SAME AS IF CREATE IPV4 RETURNS NULL
                .
                .
                .
                continue
            if tcp->payload not NULL and contains information,
                try reading payload with create_http
                if NULL
                    => last layer isn't http maybe set tcp layer to NULL (for print_flow to work confortably) ????
            
    add ethernet frame to the linked list if ethernet frame not NULL
    frame_counter++

}

print_fg(linked list) (print 20 frames at a time ? or no limit ? if no limit might lose some frames in the printing)

print entry options such has "filter" and "save flowgraph" by inputting a single char
then call function that takes an input and switch cases;

free allocations

exit();
}





sscanf entry into a char
char *case = lower(entry)
switch (case)
{
    case 's' :      //save
        function that fprintf into a file everything we printed
    case 'f' :      //filter
        sscanf entry
        .
        .
        .
        new linked list with filter to verify on each element of the original linked list (if matches condition, add in new linked list)
        print(fg)
    case 'q' :
        exiting the switch, don't forget to free allocations
    default :
        loop back into the switch (HOW ?)
}
*/