#include "array_functions.h"

//size_t matrix_array_length(const rectangle_t size)
//{
//    return size.cols * size.rows;
//}

void matrix_alloc(GameBoard_t* matrix, const rectangle_t size)
{
    matrix->array = malloc(size.rows * sizeof(int*));
    if (matrix->array != NULL)
    {
        for (int i = 0; i < size.rows; i++)
        {
            matrix->array[i] = malloc(size.cols * sizeof(int));
            if (matrix->array[i] == NULL)
            {
                printf("Not ok");
            }
        }
        for (int i = 0; i < size.rows; i++)
        {
            for (int j = 0; j < size.cols; j++)
            {
                matrix->array[i][j] = EMPTY;
            }
        }
        matrix->size = size;
        printf("All good\n");
    }
}