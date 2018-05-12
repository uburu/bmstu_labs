#include "move.h"

void move_points(double dx, double dy, double dz, Point *&obj, int amount_of_dots)
{
    for (int i = 0; i < amount_of_dots; i++){
        obj[i].x += dx;
        obj[i].y += dy;
        obj[i].z += dz;
    }
}
