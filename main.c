#include "library.h"

int main() {
    Matrix *data = malloc(sizeof(Matrix));
    data->n = 0; /* data->n = 0 fogja jelezni, hogy nincs meg eltarolva matrix */

    programMenu(data);

    /* memoriafelszabaditas a program vegen */
    if (data->matrix != NULL)
    {
        for (int i = 0; i < data->n; i++)
            free(data->matrix[i]);
        free(data->matrix);
    }
    if (data->irany != NULL)
        free(data->irany);
    if (data->forgas != NULL)
        free(data->forgas);
    free(data);

    return 0;
}