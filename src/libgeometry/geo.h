#pragma once
#include <stdbool.h>

typedef struct Point {
    double x;
    double y;
} point;
typedef struct Vector {
    double a;
    double b;
} vector;
typedef struct Segment {
    point start;
    point end;
} segment; // Отрезок

typedef struct Figure {
    int number;
    char name[100];
    double perimeter;
    double area;
    int type;
} figure;

vector findVector(point first, point second);
double lengthVector(vector vec);
double perimeterCircle(point center, double rad);
double areaCircle(point center, double rad);
double perimeterTriangle(point a, point b, point c, point d);
double areaTriangle(point a, point b, point c, point d);
