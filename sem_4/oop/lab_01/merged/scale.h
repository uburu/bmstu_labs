#ifndef SCALE_H
#define SCALE_H

#include "allocate.h"
#include "multiply.h"
#include "point.h"

double** setScaleMatrix(double x, double y, double z);
void scale(double x, double y, double z, Point *&obj, int amount_of_dots);

#endif // SCALE_H
