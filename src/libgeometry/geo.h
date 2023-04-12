#ifndef GEO_H
#define GEO_H
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

vector findVector(point first, point second);
double lengthVector(vector vec);
float perimeterCircle(point center, double rad);
float areaCircle(point center, double rad);
float perimeterTriangle(point a, point b, point c, point d);
float areaTriangle(point a, point b, point c, point d);
bool rangeIntersection(
        double firstStart,
        double firstEnd,
        double secondStart,
        double secondEnd);
bool boundingBox(segment firstSegment, segment secondSegment);

bool checkIntersection(segment ab, segment cd);
double vectorCrossProduct(vector vector1, vector vector2);
#endif