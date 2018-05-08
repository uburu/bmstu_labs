#ifndef PARSER_H
#define PARSER_H

int parser_points(struct Point *points, FILE *f);
int parser_polygons(struct Polygon *polygons, FILE *f);

#endif // PARSER_H
