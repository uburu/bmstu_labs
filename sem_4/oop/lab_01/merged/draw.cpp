#include <iostream>
#include "draw.h"

int draw(QGraphicsScene *holst, struct Point *points, struct Polygon *polygons, int num_polygons)
{
//    std::cout << "DRAW: " << std::endl;
    for(int i = 0; i < num_polygons; i++)
    {
        int j = 0;
        for(j = 0; j < (int)(sizeof(polygons[i].array)/sizeof(polygons[i].array[0])); j++)
        {
            size_t ind_1 = polygons[i].array[j];
            size_t ind_2 = polygons[i].array[j + 1];
            holst->addLine(points[ind_1].x,
                           points[ind_1].y,
                           points[ind_2].x,
                           points[ind_2].y,
                           QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));

//            std::cout << points[ind_1].x << " " << ind_1 << " " << points[ind_1].y << std::endl;
        }
        size_t ind_1 = polygons[i].array[0];
        size_t ind_2 = polygons[i].array[j];
        holst->addLine(points[ind_1].x,
                       points[ind_1].y,
                       points[ind_2].x,
                       points[ind_2].y,
                       QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));

//        std::cout << points[ind_1].x << " " << ind_1 << " " << points[ind_1].y << std::endl;
//        std::cout << std::endl;
     }

    return 0;
}
