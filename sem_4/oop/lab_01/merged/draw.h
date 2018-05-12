#include <QGraphicsScene>
#include "mainwindow.h"
#include "point.h"
#ifndef DRAW_H
#define DRAW_H

int draw(QGraphicsScene *holst, struct Point *points, struct Polygon *polygons, int num_polygons);

#endif // DRAW_H
