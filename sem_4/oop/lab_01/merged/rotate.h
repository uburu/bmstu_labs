#ifndef ROTATE_H
#define ROTATE_H

#include <cmath>
#include "allocate.h"
#include "point.h"
#include "multiply.h"

double** set_x_rotate_matrix(double x_angle);
double** set_y_rotate_matrix(double y_angle);
double** set_z_rotate_matrix(double z_angle);
void rotate(double x_angle, double y_angle, double z_angle, Point *&obj, int amount_of_dots);

#endif // ROTATE_H
