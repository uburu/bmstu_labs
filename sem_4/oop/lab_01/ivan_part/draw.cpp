#include <iostream>
#include "draw.h"

int draw(QGraphicsScene *holst, struct Point *points, struct Polygon *polygons, int num_polygons)
{
    for(int i = 0; i < num_polygons; i++)
    {
        int j = 0;
        for(j = 0; j < (int)(sizeof(polygons[i].array)/sizeof(polygons[i].array[0])); j++)
        {
            holst->addLine(points[polygons[i].array[j]].x,
                           points[polygons[i].array[j]].y,
                           points[polygons[i].array[j+1]].x,
                           points[polygons[i].array[j+1]].y,
                           QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
        }

        holst->addLine(points[polygons[i].array[0]].x,
                       points[polygons[i].array[0]].y,
                       points[polygons[i].array[j]].x,
                       points[polygons[i].array[j]].y,
                       QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));

        std::cout << std::endl;
     }

    return 0;
}
