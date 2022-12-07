#include "./headers/reader.h"
#include "./headers/tests.h"
#include "./headers/tools.h"
#include "./headers/ethernet.h"
#include "./headers/tcp.h"

#include "./headers/flowGraph.h"
#include "./headers/http.h"

#define MAX_LINE_LENGTH 3500

int main(void)
{   

    printf("Hello, please type a name of file\n");
    /* format file */
    char rawFile[50];
    scanf("%s",rawFile); // we ask user to put the name of his file
    printf("Filename : %s\n",rawFile); 
    frametostr(rawFile,"temporary_File.txt"); // we format file to "Formatted_file.txt"
    verif("temporary_File.txt","Formatted_File.txt"); 

    /* read Formatted_File and create frame */
    static int frame_counter = 0 ;
    // char line[MAX_LINE_LENGTH] = {0}; // maybe 3500 is a bit too much? 
    FILE* fd = fopen("Formatted_File.txt", "r");
    if (!fd)
    {
        puts("Failed opening Formatted_File.txt (main.c)");
        return;
    }
    
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0; 
    
    
    while ((read = getline(&line, &len, fd)) != -1)
    {
        frame_counter++;
        
    }
    free(line);
    fclose(fd);

    /* main menu */
    int boolean = 1;
    int choice = -1; 


    while (boolean == 1) {
        printf("+====================================+\n");
        printf("|               MAIN MENU            |\n");
        printf("+====================================+\n");
        printf("| 1. Print flowgraph on termial      |\n");
        printf("| 2. Export flowgraph as .txt file   |\n");
        printf("| 3. Activate/Desactivate filters    |\n");
        printf("| 4. See frame details               |\n");
        printf("| 5. Quit                            |\n");
        printf("+====================================+\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            system("clear");
            // print_flowgraph(frame *fr);
            break; 
            case 2: 
            system("clear");
            printf("====================================\n");
            // fonction to save flowgraph
            printf(" Flowgraph exported as flowgraph.txt\n");
            break;
            case 3:
            system("clear");
            printf("=====================================\n");
            printf("Activate/Desactivate filters\n");
            // fonction to activate/desactivate filters
            break;
            case 4:
            system("clear");
            int frame_number; 
            printf("=====================================\n");
            printf("Type frame number to print it's details\n");
            scanf("%d",&frame_number);
            printf("Printing details of Frame : %d\n",frame_number);
            // print_specific_frame(fr,frame_number);
            // fonction to print frame N details
            break;
            case 5:
            printf("=====================================\n");
            printf("Goodbye!\n");
            boolean = 0; 
            break;
            default:
            printf("=====================================\n");
            printf("Invalid choice\n");
            break;
        }
    }
    // delete_frame(frame);

    return 0;
}