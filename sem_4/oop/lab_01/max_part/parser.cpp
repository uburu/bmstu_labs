#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cmath>   
#include <stdlib.h>

#define PI 3.14159265  
#define N 3


///////////////////////////////////////////////////////////////PRIVATE/////////////////////////////////////////


// вывод матрицы
void printMatrix(double** data, int n, int m){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			std::cout << data[i][j] << " ";
		}
		std::cout << "\n";
	}
}

// умножение матриц
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

////////////// SCALE /////////////

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

double** allocate_matrix_rows(int n, int m)
{
    
    double **data = new double*[n];
    if (!data)
        return NULL;

    for (int i = 0; i < n; i++){
        data[i] = new double[m];
    }
    return data;
}


void setZeroResult(int n, int m, double **&data){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			data[i][j] = 0;
		}
	}
}


////////////// ROTATE /////////////



// создание матриц поворота вокруг соответствующих осей

double** set_x_rotate_matrix(double x_angle){
	double **data = allocate_matrix_rows(N,N);
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			data[i][j] = 0;
		}
	}
	data[0][0] = 1;
	data[1][1] = cos(x_angle * PI / 180);
	data[1][2] = -1 * sin(x_angle * PI / 180);
	data[2][1] = sin(x_angle * PI / 180);
	data[2][2] = cos(x_angle * PI / 180);

	return data;
}

double** set_y_rotate_matrix(double y_angle){
	double **data = allocate_matrix_rows(N,N);
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			data[i][j] = 0;
		}
	}
	data[1][1] = 1;
	data[0][0] = cos(y_angle * PI / 180);
	data[0][2] = sin(y_angle * PI / 180);
	data[2][0] = -1 * sin(y_angle * PI / 180);
	data[2][2] = cos(y_angle * PI / 180);

	return data;
}

double** set_z_rotate_matrix(double z_angle){
	double **data = allocate_matrix_rows(N,N);
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			data[i][j] = 0;
		}
	}
	data[2][2] = 1;
	data[0][0] = cos(z_angle * PI / 180);
	data[0][1] = -1 * sin(z_angle * PI / 180);
	data[1][0] = sin(z_angle * PI / 180);
	data[1][1] = cos(z_angle * PI / 180);

	return data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////




typedef struct { // координаты точек
	double x;
	double y;
	double z;
}point_t;

typedef struct { // номера точек для полигона
	int first;
	int second;
	int third;
}polygon_t;

void read_v_points(point_t *&v_obj, int &amount_of_dots, char file_path[]){ // *& - способ изменить массив в функции не возвращая его 
	int nread;
	char *line = NULL;
	size_t len = 0;
	FILE * stream;
	stream = fopen(file_path, "r");
	amount_of_dots = 0;

	while ((nread = getline(&line, &len, stream)) != -1){ // посчитали количество точек в файле
		if (line[0] == 'v')
		 	amount_of_dots += 1;
		else
			break;	
	}
	v_obj = new point_t[amount_of_dots];

	double *tmp = new double[3];

	rewind(stream);
	char *coordinates;
	double coord;
	int k = 0;
	int j = 0;
	for (int i = 0; i < amount_of_dots; i++){ // разбили по пробелам и записали в структуру
		nread = getline(&line, &len, stream);
		coordinates = strtok(line," ");
		k = 0;
		while (coordinates != NULL){
			if (*coordinates != 'v'){
				coord = atof(coordinates);
				tmp[k] = coord;
				k++;
			}
			coordinates = strtok(NULL, " ");
		}
		// запись в структуру
		v_obj[j].x = tmp[0];
		v_obj[j].y = tmp[1];
		v_obj[j].z = tmp[2];
		j++;
	}
}


// это ваня сделал сам 
 
// void read_f_points(polygon_t *&f_obj, int &amount_of_polygons, char file_path[]){
// 	int nread;
// 	char *line = NULL;
// 	size_t len = 0;
// 	FILE * stream;
// 	stream = fopen(file_path, "r");
// 	amount_of_polygons = 0;

// 	while ((nread = getline(&line, &len, stream)) != -1){ // посчитали количество точек в файле
// 		if (line[0] == 'f')
// 		 	amount_of_polygons += 1;	
// 	}
// 	f_obj = new polygon_t[amount_of_polygons];

// 	int *tmp = new int[3];

// 	rewind(stream);
// 	char *coordinates;
// 	int coord;
// 	int k = 0;
// 	int j = 0;
// 	while (nread = getline(&line, &len, stream) != -1){
// 		if (line[0] == 'v')
// 			continue; // пропускаем в файле строки с меткой v

// 		coordinates = strtok(line," ");
// 		k = 0;
// 		while (coordinates != NULL){
// 			if (*coordinates != 'f'){
// 				coord = atoi(coordinates);
// 				tmp[k] = coord;
// 				k++;
// 			}
// 			coordinates = strtok(NULL, " ");
// 		}
// 		// запись в структуру
// 		f_obj[j].first = tmp[0];
// 		f_obj[j].second = tmp[1];
// 		f_obj[j].third = tmp[2];
// 		j++;
// 	}
// }


void scale(double x, double y, double z, point_t *&obj, int amount_of_dots){
	int tmpN = 1, tmpM = 3;
	double **tmpDot = allocate_matrix_rows(tmpN, tmpM);
	double **tmpResult = allocate_matrix_rows(tmpN, tmpM);
	double **scaleMatrix = setScaleMatrix(x,y,z);
	for (int i = 0; i < amount_of_dots; i++){
		// перепишем координаты из структуры в массив для дальнейшего перемножения
		tmpDot[0][0] = obj[i].x;
		tmpDot[0][1] = obj[i].y;
		tmpDot[0][2] = obj[i].z;

		// std::cout<< "КООРДИНАТЫ ТОЧКИ: ";
		// printMatrix(tmpDot, tmpN, tmpM);
		// std::cout<< "МАТРИЦА SCALE: " << "\n";
		// printMatrix(scaleMatrix, N, N);
		multiply(tmpN, tmpM, tmpDot, N, scaleMatrix, tmpResult);
		// std::cout << "RESULT: ";
		// printMatrix(tmpResult, tmpN, tmpM);
		// std::cout << "--------------------------------------"<<"\n";
		// переписываем получившиеся новые координаты точки обратно в структуру
		obj[i].x = tmpResult[0][0];
		obj[i].y = tmpResult[0][1];
		obj[i].z = tmpResult[0][2];
		setZeroResult(tmpN, tmpM, tmpResult); // чтобы tmpResult не накапливал в себе результаты прошлого умножения
	}
}


void rotate(double x_angle, double y_angle, double z_angle, point_t *&obj, int amount_of_dots){

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
	// std::cout << "x_rotate: " << "\n";
	// printMatrix(x_rotate_matrix,N,N);
	// std::cout << "y_rotate: " << "\n";
	// printMatrix(y_rotate_matrix,N,N);
	// std::cout << "z_rotate: " << "\n";
	// printMatrix(z_rotate_matrix,N,N);
	// std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";

	// итоговая матрица поворота = z_rotat_matrix * (y_rotate_matrix * x_rotate_matrix)
	multiply(N, N, y_rotate_matrix, N, x_rotate_matrix, y_x_result);
	multiply(N, N, z_rotate_matrix, N, y_x_result, z_y_x_result);
	// std::cout<< "y_x_result: " << "\n";
	// printMatrix(y_x_result, N, N);
	// std::cout<< "z_y_x_result: " << "\n";
	// printMatrix(z_y_x_result, N, N);
	// std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";

	// умножаем координаты каждой точки на матрицу поворота z_y_x_result
	for (int i = 0; i < amount_of_dots; i++){
		// перепишем координаты из структуры в массив для дальнейшего перемножения
		tmpDot[0][0] = obj[i].x;
		tmpDot[0][1] = obj[i].y;
		tmpDot[0][2] = obj[i].z;

		// std::cout<< "КООРДИНАТЫ ТОЧКИ: ";
		// printMatrix(tmpDot, tmpN, tmpM);
		// std::cout<< "МАТРИЦА rotate: " << "\n";
		// printMatrix(z_y_x_result, N, N);
		multiply(tmpN, tmpM, tmpDot, N, z_y_x_result, tmpResult);
		// std::cout << "RESULT: ";
		// printMatrix(tmpResult, tmpN, tmpM);
		// std::cout << "--------------------------------------"<<"\n";
		// переписываем получившиеся новые координаты точки обратно в структуру
		obj[i].x = tmpResult[0][0];
		obj[i].y = tmpResult[0][1];
		obj[i].z = tmpResult[0][2];

		setZeroResult(tmpN, tmpM, tmpResult); // чтобы tmpResult не накапливал в себе результаты прошлого умножения
	}

}

void move(double dx, double dy, double dz, point_t *&obj, int amount_of_dots){
	for (int i = 0; i < amount_of_dots; i++){
		obj[i].x += dx;
		obj[i].y += dy;
		obj[i].z += dz;
	}
}

int main(){
	char file_path[] = "new.txt";
	point_t *v_obj;
	polygon_t *f_obj;
	int amount_of_dots;
	int amount_of_polygons;

	// v_obj = read_v_points(file_path, amount_of_dots); // читаем координаты каждой точки
	// f_obj = read_f_points(file_path); // читаем номера точек для полигона

	read_v_points(v_obj, amount_of_dots, file_path);
	// read_f_points(f_obj, amount_of_polygons, file_path);

	// std::cout << amount_of_dots << "\n";
	// std::cout << amount_of_polygons << "\n";

	// проверочка
	// std::cout << v_obj[0].x << " " << v_obj[0].y << " " << v_obj[0].z << "\n";
	// std::cout << f_obj[0].first << " " << f_obj[0].second << " " << f_obj[0].third << "\n";
	// std::cout << f_obj[1].first << " " << f_obj[1].second << " " << f_obj[1].third << "\n";


	// проверочка scale

	// double scale_x = 2, scale_y = 2, scale_z = 2;
	// scale(scale_x, scale_y, scale_z, v_obj, amount_of_dots);
	// std::cout << v_obj[0].x << " " << v_obj[0].y << " " << v_obj[0].z << "\n";
	// std::cout << v_obj[1].x << " " << v_obj[1].y << " " << v_obj[1].z << "\n";

	// проверочка rotate
	double rotate_x = 0, rotate_y = 30, rotate_z = 0;
	rotate(rotate_x, rotate_y, rotate_z, v_obj, amount_of_dots);
	// std::cout << v_obj[0].x << " " << v_obj[0].y << " " << v_obj[0].z << "\n";
	// std::cout << v_obj[1].x << " " << v_obj[1].y << " " << v_obj[1].z << "\n";

	for (int i = 0;i < amount_of_dots; i++)
		std::cout << v_obj[i].x << " " << v_obj[i].y << " " << v_obj[i].z << "\n";




	return 0;
}