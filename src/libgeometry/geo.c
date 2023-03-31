#include <libgeometry/geo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

vector findVector(point first, point second)
{
    vector res = {(second.x - first.x), (second.y - first.y)};
    return res;
}
double lengthVector(vector vec)
{
    return sqrt(vec.a * vec.a + vec.b * vec.b);
}

float perimeterCircle(point center, double rad)
{
    return 2 * M_PI * rad;
}
float areaCircle(point center, double rad)
{
    return M_PI * rad * rad;
}

float perimeterTriangle(point a, point b, point c, point d)
{
    float first = lengthVector(findVector(a, b));
    float second = lengthVector(findVector(b, c));
    float third = lengthVector(findVector(c, d));
    return first + second + third;
}
float areaTriangle(point a, point b, point c, point d) // По формуле Герона
{
    float p = perimeterTriangle(a, b, c, d) / 2;
    float ta = lengthVector(findVector(a, b));
    float tb = lengthVector(findVector(b, c));
    float tc = lengthVector(findVector(c, d));
    return sqrt(p * (p - ta) * (p - tb) * (p - tc));
}