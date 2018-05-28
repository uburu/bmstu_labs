#ifndef ALLOCATE_H
#define ALLOCATE_H

#include <iostream>

double** allocate_matrix_rows(int n, int m);
void setZeroResult(int n, int m, double **&data);
void delete_matrix_rows(int n, int m, double **&data);

#endif // ALLOCATE_H
