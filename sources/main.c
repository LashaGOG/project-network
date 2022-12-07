#include "./headers/reader.h"
#include "./headers/tests.h"
#include "./headers/tools.h"
#include "./headers/ethernet.h"
#include "./headers/tcp.h"

#include "./headers/flowGraph.h"
#include "./headers/http.h"

int main(void)
{   

    printf("Hello, please type a name of file\n");
    /* format file */
    char rawFile[50];
    scanf("%s",rawFile);
    printf("Filename : %s\n",rawFile);
    frametostr(rawFile,"temporary_File.txt"); 
    verif("temporary_File.txt","Formatted_File.txt"); // we put 

    /* read Formatted_File */
    
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
            break;
            case 4:
            system("clear");
            printf("=====================================\n");
            printf("Print Frame details here\n");
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

    return 0;
}