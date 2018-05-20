#include "rotate.h"

static const double PI = 3.14159265;
static const int N = 3;

static const double in_degrees = PI/180;

double** set_x_rotate_matrix(double x_angle)
{
    double **data = allocate_matrix_rows(N,N);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            data[i][j] = 0;
        }
    }
    data[0][0] = 1;
    data[1][1] = cos(x_angle * in_degrees);
    data[1][2] = -1 * sin(x_angle * in_degrees);
    data[2][1] = sin(x_angle * in_degrees);
    data[2][2] = cos(x_angle * in_degrees);

    return data;
}

double** set_y_rotate_matrix(double y_angle)
{
    double **data = allocate_matrix_rows(N,N);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            data[i][j] = 0;
        }
    }
    data[1][1] = 1;
    data[0][0] = cos(y_angle * in_degrees);
    data[0][2] = sin(y_angle * in_degrees);
    data[2][0] = -1 * sin(y_angle * in_degrees);
    data[2][2] = cos(y_angle * in_degrees);

    return data;
}

double** set_z_rotate_matrix(double z_angle)
{
    double **data = allocate_matrix_rows(N,N);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            data[i][j] = 0;
        }
    }
    data[2][2] = 1;
    data[0][0] = cos(z_angle * in_degrees);
    data[0][1] = -1 * sin(z_angle * in_degrees);
    data[1][0] = sin(z_angle * in_degrees);
    data[1][1] = cos(z_angle * in_degrees);

    return data;
}

void rotate(double x_angle, double y_angle, double z_angle, Point *&obj, int amount_of_dots)
{

    int tmpN = 1, tmpM = 3;
    double **tmpDot = allocate_matrix_rows(tmpN, tmpM);
    double **tmpResult = allocate_matrix_rows(tmpN, tmpM);

    // хранение результатов перемножения матриц
    double **y_x_result = allocate_matrix_rows(N, N);
    double **z_y_x_result = allocate_matrix_rows(N, N); // результат умножения 3-х матриц

    // получаем матрицы поворота вокруг каждой из осей
    double **x_rotate_matrix = set_x_rotate_matrix(x_angle);
    double **y_rotate_matrix = set_y_rotate_matrix(y_angle);
    double **z_rotate_matrix = set_z_rotate_matrix(z_angle);

    // итоговая матрица поворота = z_rotat_matrix * (y_rotate_matrix * x_rotate_matrix)
    multiply(N, N, y_rotate_matrix, N, x_rotate_matrix, y_x_result);
    multiply(N, N, z_rotate_matrix, N, y_x_result, z_y_x_result);

    // умножаем координаты каждой точки на матрицу поворота z_y_x_result
    for (int i = 0; i < amount_of_dots; i++){
        // перепишем координаты из структуры в массив для дальнейшего перемножения
        tmpDot[0][0] = obj[i].x;
        tmpDot[0][1] = obj[i].y;
        tmpDot[0][2] = obj[i].z;

        multiply(tmpN, tmpM, tmpDot, N, z_y_x_result, tmpResult);

        // переписываем получившиеся новые координаты точки обратно в структуру
        obj[i].x = tmpResult[0][0];
        obj[i].y = tmpResult[0][1];
        obj[i].z = tmpResult[0][2];

        setZeroResult(tmpN, tmpM, tmpResult); // чтобы tmpResult не накапливал в себе результаты прошлого умножения
    }

    delete_matrix_rows(tmpN, tmpM, tmpDot);
    delete_matrix_rows(tmpN, tmpM, tmpResult);
    delete_matrix_rows(N, N, y_x_result);
    delete_matrix_rows(N, N, z_y_x_result);
    delete_matrix_rows(N, N, x_rotate_matrix);
    delete_matrix_rows(N, N, y_rotate_matrix);
    delete_matrix_rows(N, N, z_rotate_matrix);
}
