#include <iostream>
#include "point.h"
#include <cstring>
#include <cstdlib>

int parser_points(struct Point *points, FILE *f)
{
    char *line = NULL;
    size_t mem_size = 0;
    double num = 0;
    int read = 0;
    int i = 0;
    int j = 0;

    while (read != -1)
    {
        read = getline(&line, &mem_size, f);
        char *pch = strtok(line," ");
        if(strchr(line, 'f'))
            break;

        while (pch != NULL)
        {
            if(*pch != 'v')
            {
                num = atof(pch);
                if(j == 0)
                    points[i].x = num;
                else if(j == 1)
                    points[i].y = num;
                else if(j == 2)
                    points[i].z = num;
                if(j == 2)
                {
                    j = -1;
                    i++;
                }
                j++;
            }
            pch = strtok(NULL," ");
        }
    }

    return 0;
}


int parser_polygons(struct Polygon *polygons, FILE *f)
{
    char *line = NULL;
    size_t mem_size = 0;
    double num = 0;
    int read = 0;
    int i = 0;
    int count_polygons = 0;

    while (read != -1)
    {
        read = getline(&line, &mem_size, f);
        if(strchr(line, 'f'))
        {
            char *pch = strtok (line," ");
            polygons[i].array = nullptr;
            while (pch != NULL)
            {
                if(strchr(pch, '\n'))
                {
                    if(atof(pch))
                    {
                        num = atof(pch);
                        count_polygons++;
                        polygons[i].array =(int*) realloc(polygons[i].array, count_polygons);
                        polygons[i].array[count_polygons-1] = num - 1;
                    }
                    i++;
                    count_polygons = 0;
                    pch = strtok (NULL," ");
                    continue;
                }
                if(*pch != 'f')
                {
                    num = atof(pch);
                    count_polygons++;
                    polygons[i].array =(int*) realloc(polygons[i].array, count_polygons);
                    polygons[i].array[count_polygons-1] = num - 1;
                }
                pch = strtok(NULL," ");
            }
        }

    }

    return 0;

}
