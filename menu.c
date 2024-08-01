#include "library.h"

void programMenu(Matrix *data)
{
    char *buffer = malloc(sizeof(char) * BUFFER_MAX); /* buffer -- szovegbeolvasashoz seged */
    int option;                                       /* option -- menupont valaszto */

    while (1)
    {
        menuText();

        /* default option ertek minden beolvasas elott -1, 
           igy sikeres beolvasas eseten ha nem jo adatot adott meg a felhasznalo, a default erteket vizsgalja a switch */
        option = -1;

        printf("\nOption: ");
        if (fgets(buffer, BUFFER_MAX, stdin) != NULL)
        {
            removeNewline(buffer);
            sscanf(buffer, "%d", &option);
            printf("\n");

            if (option == 5) break; // exit
            chooseOption(option, data);
        }

        if (feof(stdin)) break;
    }

    free(buffer);
}

void menuText()
{
    char title[] = "| SPIRAL MATRIX PROGRAM |";

    printf("\n");
    titleBorder(title);
    printf("%s\n", title);
    titleBorder(title);
    printf("0\tUser guide\n");
    printf("1\tGenerate a matrix\n");
    printf("2\tSave a matrix\n");
    printf("3\tLoad a matrix\n");
    printf("4\tPrint current matrix\n");
    printf("5\tExit\n");
}

void titleBorder(char title[])
{
    for (int i = 0; i < (int)strlen(title); i++)
        printf("-");
    printf("\n");
}

void chooseOption(int option, Matrix *data)
{
    switch (option)
    {
        case 0: // user guide
            userGuide();
            break;
        case 1: // generate matrix
            generateMatrix(data);
            break;
        case 2: // save matrix
            saveMatrix(data);
            break;
        case 3: // load matrix
            loadMatrix(data);
            break;
        case 4: // print matrix
            printMatrix(data);
            break;
        default:
            printf("Incorrect option chosen!\n");
            break;
    }
}

void userGuide()
{
    char guideTitle[] = "| USER GUIDE |";

    titleBorder(guideTitle);
    printf("%s\n", guideTitle);
    titleBorder(guideTitle);
    printf("This program helps you draw spiral matrices. The menu options can be chosen by entering their corressponding numbers in the main menu.\n");
    printf("The menu options work as follows:\n\n");

    printf("0\tUser guide\n");
    printf("Opens this user guide.\n\n");

    printf("1\tGenerate a matrix\n");
    printf("Generates a (new) spiral matrix from the entered data.\n");
    printf("Required data: n - number of rows and columns; irany - starting direction of spiral; forgasi irany - turning direction of spiral.\n\n");

    printf("2\tSave a matrix\n");
    printf("If there is a matrix stored in the program, it saves it to a file corressponding to the data of the matrix.\n\n");

    printf("3\tLoad a matrix\n");
    printf("Loads a matrix from a file based on the entered filename.\n\n");

    printf("4\tPrint current matrix\n");
    printf("Prints the currently stored matrix on the standard output (terminal).\n\n");

    printf("5\tExit\n");
    printf("Exits the program.\n\n");
}
