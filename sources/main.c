#include "./headers/reader.h"
#include "./headers/tests.h"
#include "./headers/tools.h"
#include "./headers/ethernet.h"
#include "./headers/tcp.h"

#include "./headers/flowGraph.h"
#include "./headers/http.h"

#define MAX_LINE_LENGTH 5000

int main(void)
{   
    FILE *reset = fopen("temporary_File.txt", "w");
    fclose(reset);
    reset = fopen("Formatted_File.txt", "w");

    printf("Hello, please type a name of file\n");
    /* format file */
    char rawFile[50];
    scanf("%s",rawFile); // we ask user to put the name of his file
    printf("Filename : %s\n",rawFile); 
    frametostr(rawFile,"temporary_File.txt"); // we format file to "Formatted_file.txt"
    verif("temporary_File.txt","Formatted_File.txt"); 

    /* read Formatted_File and create frame */
    FILE* file = fopen("Formatted_File.txt", "r");
    if (!file)
    {
        puts("Failed opening Formatted_File.txt (main.c)");
    }
    
    static int frame_counter = 0 ;
    frame *list_frames = NULL; 
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        // remove newline character from the line
        line[strcspn(line, "\n")] = 0;
        char* str = strdup(line);
        str[strlen(str)] = '\0';

        // create a new node with the line as data
        // frame* newFrame = createNode(line);

        // // add the node to the end of linked list
        addLast(&list_frames, str, &frame_counter);
        free(str);
    }
    fclose(file); // close file
    
    frame* ptr = list_frames;

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
                //system("clear");
                print_flowgraph(ptr);
                break; 
            case 2: 
                //system("clear");
                printf("====================================\n");
                // fonction to save flowgraph
                printf(" Flowgraph exported as flowgraph.txt\n");
                break;
            case 3:
                //system("clear");
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
                print_specific_frame(ptr, frame_number);
                puts("");
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
    delete_linked_frames(list_frames);

    return 0;
}