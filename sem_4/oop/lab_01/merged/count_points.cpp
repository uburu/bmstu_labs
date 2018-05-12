#include <iostream>

int count(int *n, FILE *f, char type)
{
    char *line = NULL;
    size_t mem_size = 0;
    int read = 0;

    while (read != -1)
    {
        read = getline(&line, &mem_size, f);
        if(strchr(line, type))
            *n = *n + 1;
    }

    return 0;
}
