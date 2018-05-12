#include "allocate.h"

double** allocate_matrix_rows(int n, int m)
{

    double **data = new double*[n];
    if (!data)
        return NULL;

    for (int i = 0; i < n; i++){
        data[i] = new double[m];
    }

    setZeroResult(n, m, data);

    return data;
}


void setZeroResult(int n, int m, double **&data)
{
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            data[i][j] = 0;
        }
    }
}
