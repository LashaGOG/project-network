#include "./headers/reader.h"
//#include "./headers/tests.h"
#include "./headers/tools.h"
#include "./headers/ethernet.h"
#include "./headers/tcp.h"

#include "./headers/flowGraph.h"
#include "./headers/http.h"

#define MAX_LINE_LENGTH 5000

int main(void)
{   
    
    /* format file */
    char rawFile[50];
    int file_exists = 0 ; 
    FILE *rFile; 
    while (file_exists == 0) { // user rests in this boucle till he does not enter a name of existing file
        printf("Hello, please type a name of file\n");
        printf("Type Quit/quit to end the exuction of program\n");
        scanf("%s",rawFile); // we ask user to put the name of his file
        if (strcmp("Quit",rawFile) == 0 || strcmp("quit",rawFile) == 0) return 0 ; // end the program
        rFile = fopen(rawFile,"r");
        if (rFile) {
            printf("Analyzing %s :\n",rawFile);
            fclose(rFile);
            break;
        }
        printf("The file named %s does not exist\n",rawFile);

    }
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
    
    /* main menu */
    int boolean = 1;
    int choice = -1; 

    char *f = NULL;

    
    
    while (boolean == 1) {

        printf("+====================================+\n");
        printf("|             MAIN  MENU             |\n");
        printf("+====================================+\n");
        printf("| 1. Print flowgraph on termial      |\n");
        printf("| 2. Export flowgraph as .txt file   |\n");
        printf("| 3. Activate/Desactivate filters    |\n");
        printf("| 4. See frame details               |\n");
        printf("| 5. Quit                            |\n");
        printf("+====================================+\n");
        printf(" Enter your choice: ");

        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 5)
        {
            switch (choice) {
                case 1:
                    system("clear");
                    print_flowgraph(list_frames, f); // fonction to print flowgraph in terminal
                    break; 
                case 2: 
                    //system("clear");
                    printf("====================================\n");
                    FILE *flowGrap_out = fopen("Flopgraph.txt","w");
                    fprint_flowgraph(flowGrap_out, list_frames, f); // fonction export flowgraph
                    printf(" Flowgraph exported as Flopgraph.txt\n");
                    fclose(flowGrap_out);
                    break;
                case 3:
                    //system("clear");
                    printf("=====================================\n");
                    printf("Activate/Desactivate filters\n");
                    if (f != NULL)
                    {
                        if (strlen(f) != 0)  //if f isn't empty, free it to avoid leaks
                            free(f);
                    }
                    f = filter(list_frames);  // fonction to activate/desactivate filters
                    break;
                case 4:
                    system("clear");
                    int frame_number; 
                    printf("=====================================\n");
                    printf("Type frame number to print it's details\n");
                    scanf("%d",&frame_number);
                    printf("Printing details of Frame : %d\n",frame_number);
                    print_specific_frame(list_frames, frame_number); // fonction to print frame N details
                    puts("");
                    break;
                case 5:
                    printf("=====================================\n");
                    printf("Goodbye!\n");
                    boolean = 0; 
                    system("clear");
                    break;
                default:
                    printf("=====================================\n");
                    printf("Invalid choice\n");
                    break;
            }
        }
        fflush(stdin); //reset 
    }
    
    if (f != NULL)
    {
        if (strlen(f) != 0)
            free(f);
    }
    delete_frame(list_frames);
    remove("temporary_file.txt");
    remove("Formatted_File.txt");
    return 0;
}