#include <iostream>
#include "point.h"
#include <cstring>
#include <cstdlib>

static const int x = 0;
static const int y = 1;
static const int z = 2;

static const int ok = 0;
static const int memory = 1;

int parser_points(struct Point *points, FILE *f)
{
    char *line = NULL;
    size_t mem_size = 0;
    double num = 0;
    int read = 0;
    int i = 0;
    int j = 0;
    int error = ok;

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
                if(j == x)
                    points[i].x = num;
                else if(j == y)
                    points[i].y = num;
                else if(j == z)
                    points[i].z = num;
                if(j == z)
                {
                    j = -1;
                    i++;
                }
                j++;
            }
            pch = strtok(NULL," ");
        }
    }

    return error;
}


int parser_polygons(struct Polygon *polygons, FILE *f)
{
    char *line = NULL;
    size_t mem_size = 0;
    double num = 0;
    int read = 0;
    int i = 0;
    int count_polygons = 0;
    int alloc_mem = 10;
    int error = ok;

    while (read != -1)
    {
        read = getline(&line, &mem_size, f);
        if(strchr(line, 'f'))
        {
            char *pch = strtok (line," ");
            polygons[i].array = (int*) malloc(alloc_mem * sizeof(int)); // выделил память
            if(!polygons[i].array) // проверил на выделение
                error = memory;
            else
            {
                while (pch != NULL)
                {
                    if(strchr(pch, '\n'))
                    {
                        if(atof(pch))
                        {
                            num = atof(pch);
                            count_polygons++;
                            if(count_polygons > alloc_mem)
                            {
                                alloc_mem += 10;
                                polygons[i].array =(int*) realloc(polygons[i].array, alloc_mem);
                            }
                            if(!polygons[i].array)
                                error = memory;
                            else
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
                        if(count_polygons > alloc_mem)
                        {
                            alloc_mem += 10;
                            polygons[i].array =(int*) realloc(polygons[i].array, alloc_mem);
                        }
                        if(!polygons[i].array)
                            error = memory;
                        else
                            polygons[i].array[count_polygons-1] = num - 1;
                    }
                    pch = strtok(NULL," ");
                }
              }
            }
    }

    return error;

}
