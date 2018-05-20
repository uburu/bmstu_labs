#include "scale.h"

static const int N = 3;

double** setScaleMatrix(double x, double y, double z)
{

    double **data = new double*[N];
    if (!data)
        return NULL;

    for (int i = 0; i < N; i++){
        data[i] = new double[N];
        for (int j = 0 ; j < N; j++){
            data[i][j] = 0;
        }
    }

    data[0][0] = x;
    data[1][1] = y;
    data[2][2] = z;

    return data;
}

void scale(double x, double y, double z, Point *&obj, int amount_of_dots)
{
    int tmpN = 1, tmpM = 3;
    double **tmpDot = allocate_matrix_rows(tmpN, tmpM);
    double **tmpResult = allocate_matrix_rows(tmpN, tmpM);
    double **scaleMatrix = setScaleMatrix(x,y,z);

    for (int i = 0; i < amount_of_dots; i++){
        // перепишем координаты из структуры в массив для дальнейшего перемножения
        tmpDot[0][0] = obj[i].x;
        tmpDot[0][1] = obj[i].y;
        tmpDot[0][2] = obj[i].z;

        multiply(tmpN, tmpM, tmpDot, N, scaleMatrix, tmpResult);

        // переписываем получившиеся новые координаты точки обратно в структуру
        obj[i].x = tmpResult[0][0];
        obj[i].y = tmpResult[0][1];
        obj[i].z = tmpResult[0][2];
        setZeroResult(tmpN, tmpM, tmpResult); // чтобы tmpResult не накапливал в себе результаты прошлого умножения
    }

    delete_matrix_rows(tmpN, tmpM, tmpDot);
    delete_matrix_rows(tmpN, tmpM, tmpResult);
    delete_matrix_rows(N, N, scaleMatrix);
}
