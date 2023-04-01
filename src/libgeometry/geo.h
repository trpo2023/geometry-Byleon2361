#ifndef GEO_H
#define GEO_H
typedef struct Point {
    double x;
    double y;
} point;
typedef struct Vector {
    double a;
    double b;
} vector;

vector findVector(point first, point second);
double lengthVector(vector vec);
float perimeterCircle(point center, double rad);
float areaCircle(point center, double rad);
float perimeterTriangle(point a, point b, point c, point d);
float areaTriangle(point a, point b, point c, point d);

#endif