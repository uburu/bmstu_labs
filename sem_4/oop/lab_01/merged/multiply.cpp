#include "multiply.h"
#include <iostream>

void multiply(int n1, int m1, double **a, int m2, double **b, double **&result)
{
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            for (int k = 0; k < m1; k++)
            {
                result[i][j] += (a[i][k]) * (b[k][j]);
            }
        }
    }
}
