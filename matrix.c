#include "library.h"

int** generateMatrix_temp(int *n)
{
    int localN;
    char dir[30];
    char turn[30];
    printf("n = ");
    scanf("%d", &localN);
    while (getchar() != '\n')
    {
    }
    while (localN < 1 || localN > 20)
    {
        printf("The provided value is not between 1 and 20.\n");
        printf("n = ");
        scanf("%d", &localN);
        while (getchar() != '\n')
        {
        }
    }

    printf("irany: ");
    fgets(dir, 30, stdin);

    printf("forgasi irany: ");
    fgets(turn, 30, stdin);
    printf("irany: %s, forgasi: %s\n", dir, turn);
    printf("int irany: %d, int forgasi: %d\n", atoi(dir), atoi(turn));

    int **matrix = malloc(localN * sizeof(int));
    for (int i = 0; i < localN; i++)
    {
        matrix[i] = malloc(localN * sizeof(int));
    }

    for (int i = 0; i < localN; i++)
    {
        for (int j = 0; j < localN; j++)
        {
            matrix[i][j] = i + j;
        }
    }
    *n = localN;

    return matrix;
}

void generateMatrix(Matrix* data)
{
    int n = 0;                                        /* n -- beolvasott n szamot tarolja */
    char *buffer = malloc(sizeof(char) * BUFFER_MAX); /* buffer -- szam beolvasasahoz seged */
    char *dir = malloc(sizeof(char) * BUFFER_MAX);    /* dir -- beolvasott kezdo iranyt tarolja */
    char *turn = malloc(sizeof(char) * BUFFER_MAX);   /* turn -- beolvasott forgasi iranyt tarolja */

    /* n beolvasasa */
    printf("n (1-20) = ");
    while ((n < 1 || n > 20) && (fgets(buffer, BUFFER_MAX, stdin) != NULL))
    {
        sscanf(buffer, "%d", &n);
        if (n < 1 || n > 20)
        {
            printf("The provided value is not between 1 and 20.\n");
            printf("n (1-20) = ");
        }
    }

    /* kezdo irany beolvasasa */
    if (!feof(stdin) && !ferror(stdin))
        printf("Starting direction (balra|fel|jobbra|le): ");
    while ((fgets(dir, BUFFER_MAX, stdin) != NULL) && !strEq(dir, "balra\n") && !strEq(dir, "fel\n") && !strEq(dir, "jobbra\n") && !strEq(dir, "le\n"))
    {
        printf("Starting direction is incorrect!\n");
        printf("Starting direction (balra|fel|jobbra|le): ");
    }

    /* forgasi irany beolvasasa */
    if (!feof(stdin) && !ferror(stdin))
        printf("Turning direction (cw|ccw): ");
    while ((fgets(turn, BUFFER_MAX, stdin) != NULL) && !strEq(turn, "cw\n") && !strEq(turn, "ccw\n"))
    {
        printf("Turning direction is incorrect!\n");
        printf("Turning direction (cw|ccw): ");
    }

    /* ha minden adatot sikeresen beolvastunk, akkor vegezzuk csak el a matrixgeneralast */
    if (!feof(stdin) && !ferror(stdin))
    {
        removeNewline(dir);
        removeNewline(turn);

        matrixAlloc(data, n, strlen(dir), strlen(turn));

        /* beolvasott adatok tarolasa az uj matrixban */
        data->n = n;
        strcpy(data->irany, dir);
        strcpy(data->forgas, turn);

        /* matrix feltoltese szamokkal */
        fillMatrix(data);
    }

    /* memoriafelszabaditas */
    free(dir);
    free(turn);
    free(buffer);
}

void printMatrix(Matrix *data)
{
    if (data->n == 0)
        printf("There is no matrix to print!\n");
    else
        drawMatrix(data->n, data->matrix, stdout);
}

void saveMatrix(Matrix *data)
{
    if (data->n == 0)
    {
        printf("There is no matrix to save!\n");
    }
    else
    {
        /* dir -- az irany 1 karakteres roviditeset adja meg */
        char *dir = malloc(sizeof(char) * 2);
        *dir = charDir(data->irany);

        /* charN -- n szamot szovegge alakitva tarolja el */
        char *charN = malloc(sizeof(int) * (numOfDigits(data->n) + 1));
        sprintf(charN, "%d", data->n);

        /* filenev osszerakasa */
        char opener[] = "spiral";
        char *filename = malloc(sizeof(char) * (strlen(opener) + strlen(data->forgas) + strlen(charN) + 6));
        strcpy(filename, opener);
        strcpy(filename + strlen(filename), charN);
        strcpy(filename + strlen(filename), dir);
        strcpy(filename + strlen(filename), data->forgas);
        strcpy(filename + strlen(filename), ".txt");

        FILE *f = fopen(filename, "w");
        if (f == NULL)
        {
            printf("Error saving matrix to file!\n");
        }
        else
        {
            drawMatrix(data->n, data->matrix, f);
            printf("Matrix saved to: %s\n", filename);
        }
        fclose(f);

        /* memoriafelszabaditas */
        free(dir);
        free(charN);
        free(filename);
    }
}

void loadMatrix(Matrix *data)
{
    int i = 0;
    char *fileName = malloc(sizeof(char) * BUFFER_MAX); /* fileName -- a beolvasando file nevet fogja tarolni */
    int *nums = malloc(sizeof(int));                    /* nums -- ebben taroljuk ideiglenesen a file-bol beolvasott szamokat */
    char *dir = malloc(sizeof(char) * 7);               /* dir -- ideiglenesen tarolja a megallapitott kezdo iranyt */
    char *turn = malloc(sizeof(char) * 4);              /* turn -- ideiglenesen tarolja a megallapitott forgasi iranyt */

    /* filenev beolvasasa es file megnyitasa, ha letezik az adott file */
    printf("Filename: ");
    fgets(fileName, BUFFER_MAX, stdin);
    if (!feof(stdin) && !ferror(stdin))
        removeNewline(fileName);
    FILE *f = fopen(fileName, "r");
    while (!feof(stdin) && !ferror(stdin) && f == NULL)
    {
        printf("The file does not exist! Please enter a valid and existing filename (eg. spiral3ucw.txt)!\n");
        printf("Filename: ");
        fgets(fileName, BUFFER_MAX, stdin);
        if (!feof(stdin) && !ferror(stdin))
        {
            removeNewline(fileName);
            f = fopen(fileName, "r");
        }
    }

    if (!feof(stdin) && !ferror(stdin))
    {
        /* szamok beolvasasa a file-bol */
        while (fscanf(f, "%d", &nums[i]) != EOF)
        {
            i++;
            nums = realloc(nums, sizeof(int) * (i + 1));
        }
        int n = (int)sqrt((double)i);

        /* kozeppont megkeresese a kezdo irany es forgasi irany megallapitasahoz */
        int j = 0;
        int k = 0;
        findCenter(nums, n, &j, &k);

        /* kezdo irany megallapitasa */
        findDir(nums, n, dir, &j, &k);

        /* forgasi irany megallapitasa */
        findTurn(nums, dir, turn, n, j, k);

        /* (uj) matrix adatainak memoria allokalasa */
        matrixAlloc(data, n, strlen(dir), strlen(turn));

        /* matrix adatainak feltoltese */
        data->n = n;
        strcpy(data->irany, dir);
        strcpy(data->forgas, turn);
        int m = 0;
        for (int p = 0; p < n; p++)
        {
            for (int q = 0; q < n; q++)
            {
                data->matrix[p][q] = nums[m];
                m++;
            }
        }

        printf("Matrix loaded from %s!\n", fileName);
    }

    /* memoriafelszabaditas */
    if (f != NULL)
        fclose(f);
    free(dir);
    free(turn);
    free(nums);
    free(fileName);
}
