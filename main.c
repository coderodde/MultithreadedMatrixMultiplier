#include "matrix.h"
#include "matrix_algorithm.h"
#include <stdio.h>


int main() {
    matrix_t a;
    matrix_t b;
    
    matrix_t_init(&a, 2, 2);
    matrix_t_init(&b, 2, 2);
    
    matrix_t_set(&a, 0, 0, 1.0);
    matrix_t_set(&a, 1, 0, 2.0);
    matrix_t_set(&a, 0, 1, 3.0);
    matrix_t_set(&a, 1, 1, 4.0);
    
    matrix_t_set(&b, 0, 0, 1.0);
    matrix_t_set(&b, 1, 0, 2.0);
    matrix_t_set(&b, 0, 1, 3.0);
    matrix_t_set(&b, 1, 1, 4.0);
    
    matrix_t* ab = matrix_t_multiply(&a, &b);
    matrix_t* ab2 = matrix_t_multiply_parallel(&a, &b);
    matrix_t_print(ab);
    return 0;
}
