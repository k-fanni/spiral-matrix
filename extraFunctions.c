#include "library.h"

/***** SEGEDFUGGVENYEK *****/

void matrixAlloc(Matrix *data, int n, int lengthDir, int lengthTurn)
{
    /* memoria allokalasa az uj matrixnak es a hozza tartozo adatoknak
        ha data->n == 0, akkor meg nincs tarolva matrix a memoriaban, kulonben a regi matrix helyett keszitjuk el az uj matrixot */
    if (data->n == 0)
    {
        data->irany = malloc(sizeof(char) * (lengthDir + 1));
        data->forgas = malloc(sizeof(char) * (lengthTurn + 1));
        data->matrix = malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++)
            data->matrix[i] = malloc(n * sizeof(int *));
    }
    else
    {
        data->irany = realloc(data->irany, sizeof(char) * (lengthDir + 1));
        data->forgas = realloc(data->forgas, sizeof(char) * (lengthTurn + 1));
        for (int i = 0; i < data->n; i++)
            free(data->matrix[i]);
        data->matrix = realloc(data->matrix, n * sizeof(int *));
        for (int i = 0; i < n; i++)
            data->matrix[i] = malloc(n * sizeof(int *));
    }
}

void fillMatrix(Matrix *data)
{
    int num = 1;     /* num -- ez adja meg, milyen szamot kell eppen a matrixba irnunk */
    int repeats = 1; /* repeats -- megadja, egy iranyba hany lepest kell tennunk */
    int step = 0;    /* step -- ezzel szamoljuk az egy iranyba tett lepeseket */

    /* dir -- olvashatosag es konnyu iranyvaltas miatt egy karakterkent taroljuk az iranyt, ezt fogjuk valtoztatni */
    char dir = charDir(data->irany);
    /* initialDir -- a kezdo iranyt lemasoljuk dir-bol, ezt nem fogjuk valtoztatni, konnyen lehet a kezdo iranyra kesobb igy hivatkozni */
    char initialDir = dir;

    /* kozeppont kijelolese es feltoltese -- innen fogunk lepegetni es fordulni a feltoltes kozben */
    int i = data->n / 2;
    int j = i;
    if (data->n % 2 == 0) /* ha n paros szam, a kozeppont nem biztos, hogy az elsokent kiszamolt i,j indexnel lesz */
        evenCenter(&i, &j, data->irany, data->forgas);
    data->matrix[i][j] = num;

    /* kozeppont utan onnan elindulva feltoltjuk szamokkal a matrixot */
    while (++num <= (data->n * data->n))
    {
        if (step == repeats)
        {
            step = 0;

            /* ha megvolt egy iranyba az osszes lepes, akkor fordulunk a megadott forgasi iranyban */
            if (strEq(data->forgas, "cw"))
                dir = turnCw(dir);
            else
                dir = turnCcw(dir);

            /* a kezdo es jelenlegi iranytol fuggoen megemeljuk 1-el a repeats-et */
            if ((initialDir == 'l' || initialDir == 'r') && (dir == 'l' || dir == 'r'))
                repeats++;
            if ((initialDir == 'u' || initialDir == 'd') && (dir == 'u' || dir == 'd'))
                repeats++;
        }

        /* lepunk egyet a megadott iranyba */
        if (dir == 'r') j++;
        if (dir == 'd') i++;
        if (dir == 'l') j--;
        if (dir == 'u') i--;

        /* az uj pozicio feltoltese a megfelelo szammal */
        data->matrix[i][j] = num;
        step++;
    }
}

bool strEq(char a[], char b[])
{
    return strcmp(a, b) == 0;
}

void evenCenter(int *i, int *j, char irany[], char forgas[])
{
    if ((strEq(irany, "fel") && strEq(forgas, "cw")) || (strEq(irany, "jobbra") && strEq(forgas, "ccw")))
    {
        *j = *j - 1;
    }
    else if ((strEq(irany, "jobbra") && strEq(forgas, "cw")) || (strEq(irany, "le") && strEq(forgas, "ccw")))
    {
        *i = *i - 1;
        *j = *j - 1;
    }
    else if ((strEq(irany, "le") && strEq(forgas, "cw")) || (strEq(irany, "balra") && strEq(forgas, "ccw")))
    {
        *i = *i - 1;
    }
}

char charDir(char irany[])
{
    char dir;
    if (strEq(irany, "jobbra"))
        dir = 'r';
    else if (strEq(irany, "fel"))
        dir = 'u';
    else if (strEq(irany, "balra"))
        dir = 'l';
    else
        dir = 'd';
    return dir;
}

char turnCw(char dir)
{
    if (dir == 'r')
        dir = 'd';
    else if (dir == 'd')
        dir = 'l';
    else if (dir == 'l')
        dir = 'u';
    else
        dir = 'r';

    return dir;
}

char turnCcw(char dir)
{
    if (dir == 'r')
        dir = 'u';
    else if (dir == 'u')
        dir = 'l';
    else if (dir == 'l')
        dir = 'd';
    else
        dir = 'r';

    return dir;
}

int numOfDigits(int num)
{
    int count = 0;
    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

void drawMatrix(int n, int **matrix, FILE *f)
{
    /* maxDigits -- megadja, hany szamjegybol all a matrixban szereplo legnagyobb szam */
    int maxDigits = numOfDigits(n * n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            /* currDigits -- megadja, hany szamjegybol all a matrix jelenleg vizsgalt eleme */
            int currDigits = numOfDigits(matrix[i][j]);
            while (currDigits != maxDigits)
            {
                fprintf(f, " ");
                currDigits++;
            }
            fprintf(f, "%d ", matrix[i][j]);
        }
        fprintf(f, "\n");
    }
}

void removeNewline(char *s)
{
    int l = strlen(s);
    if (s[l - 1] == '\n')
        s[l - 1] = '\0';
}

void findCenter(int *nums, int n, int *j, int *k)
{
    while (nums[*j + *k] != 1 && (*j + *k) < (n * n))
    {
        *k = *k + 1;
        if (*k == n)
        {
            *k = 0;
            *j += n;
        }
    }
    *j = *j / n;
}

void findDir(int *nums, int n, char *dir, int *j, int *k)
{
    if ((*j - 1) >= 0 && nums[(n * (*j - 1)) + *k] == 2)
    {
        strcpy(dir, "fel");
        *j = *j - 1;
    }
    else if ((*j + 1) < n && nums[(n * (*j + 1)) + *k] == 2)
    {
        strcpy(dir, "le");
        *j = *j + 1;
    }
    else if ((*k - 1) >= 0 && nums[(n * *j) + *k - 1] == 2)
    {
        strcpy(dir, "balra");
        *k = *k - 1;
    }
    else
    {
        strcpy(dir, "jobbra");
        *k = *k + 1;
    }
}

void findTurn(int *nums, char *dir, char *turn, int n, int j, int k)
{
    if (strEq(dir, "fel"))
    {
        if ((k - 1) >= 0 && nums[(n * j) + k - 1] == 3)
            strcpy(turn, "ccw");
        else
            strcpy(turn, "cw");
    }
    else if (strEq(dir, "le"))
    {
        if ((k - 1) >= 0 && nums[(n * j) + k - 1] == 3)
            strcpy(turn, "cw");
        else
            strcpy(turn, "ccw");
    }
    else if (strEq(dir, "balra"))
    {
        if ((j - 1) >= 0 && nums[(n * (j - 1)) + k] == 3)
            strcpy(turn, "cw");
        else
            strcpy(turn, "ccw");
    }
    else
    {
        if ((j - 1) >= 0 && nums[(n * (j - 1)) + k] == 3)
            strcpy(turn, "ccw");
        else
            strcpy(turn, "cw");
    }
}