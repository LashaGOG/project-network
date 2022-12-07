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
    char line[MAX_LINE_LENGTH] = {0}; // maybe 3500 is a bit too much? 
    frame *frame;
    FILE *fp = fopen("Formatted_file.txt", "r");
    while (fgets(line, MAX_LINE_LENGTH, fp)) 
    {
        frame = create_frame(line,&frame_counter);
        fgets(line, MAX_LINE_LENGTH, fp);
    }
    fclose(fp);

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
            printf("We print flowgraph here\n");
            // fonction to print flowgraph
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
            printf("=====================================\n");
            printf("Print Frame details here\n");
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
    delete_frame(frame);

    return 0;
}