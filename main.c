#include "matrix.h"
#include "matrix_algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static matrix_t* create_random_matrix(size_t rows, size_t cols)
{
    size_t x;
    size_t y;
    matrix_t* m = malloc(sizeof(*m));
    matrix_t_init(m, rows, cols);
    
    for (x = 0; x < cols; ++x)
    {
        for (y = 0; y < rows; ++y)
        {
            matrix_t_set(m, x, y, ((double) rand()) / RAND_MAX);
        }
    }
    
    return m;
}

static size_t get_milliseconds()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}

static int matrix_equals(matrix_t* a, matrix_t* b)
{
    size_t x;
    size_t y;
    
    if (a->m_cols != b->m_cols || a->m_rows != b->m_rows)
    {
        return 0;
    }
    
    for (y = 0; y < a->m_rows; ++y)
    {
        for (x = 0; x < a->m_cols; ++x)
        {
            if (matrix_t_get(a, x, y) != matrix_t_get(b, x, y))
            {
                return 0;
            }
        }
    }
    
    return 1;
}

int main() {
    size_t start_time;
    size_t end_time;
    matrix_t* ab1;
    matrix_t* ab2;
    
    srand((unsigned int) time(NULL));
    
    matrix_t* a = create_random_matrix(300, 300);
    matrix_t* b = create_random_matrix(300, 300);
    
    start_time = get_milliseconds();
    ab1 = matrix_t_multiply(a, b);
    end_time = get_milliseconds();
    
    printf("Single-threaded multiplication in %zu milliseconds.\n",
           end_time - start_time);
    
    start_time = get_milliseconds();
    ab2 = matrix_t_multiply_parallel(a, b);
    end_time = get_milliseconds();
    
    printf("%zu-threaded multiplication in %zu milliseconds.\n",
           sysconf(_SC_NPROCESSORS_ONLN),
           end_time - start_time);
    
    printf("Algorithms agree: %d\n", matrix_equals(ab1, ab2));
    return 0;
}
