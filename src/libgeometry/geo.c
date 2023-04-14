#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <libgeometry/exception.h>
#include <libgeometry/geo.h>

vector findVector(point first, point second)
{
    vector res = {(second.x - first.x), (second.y - first.y)};
    return res;
}
double lengthVector(vector vec)
{
    return sqrt(vec.a * vec.a + vec.b * vec.b);
}

double perimeterCircle(point center, double rad)
{
    return 2 * M_PI * rad;
}
double areaCircle(point center, double rad)
{
    return M_PI * rad * rad;
}

double perimeterTriangle(point a, point b, point c, point d)
{
    double first = lengthVector(findVector(a, b));
    double second = lengthVector(findVector(b, c));
    double third = lengthVector(findVector(c, d));
    return first + second + third;
}
double areaTriangle(point a, point b, point c, point d) // По формуле Герона
{
    double p = perimeterTriangle(a, b, c, d) / 2;
    double ta = lengthVector(findVector(a, b));
    double tb = lengthVector(findVector(b, c));
    double tc = lengthVector(findVector(c, d));
    return sqrt(p * (p - ta) * (p - tb) * (p - tc));
}