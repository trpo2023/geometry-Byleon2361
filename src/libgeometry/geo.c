#include <libgeometry/geo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

vector funVector(point first, point second)
{
    vector res = {(second.x - first.x), (second.y - first.y)};
    return res;
}
double lenVector(vector vec)
{
    return sqrt(vec.a * vec.a + vec.b * vec.b);
}

float pcircle(point center, double rad)
{
    return 2 * M_PI * rad;
}
float acircle(point center, double rad)
{
    return M_PI * rad * rad;
}

float ptriangle(point a, point b, point c, point d)
{
    float first = lenVector(funVector(a, b));
    float second = lenVector(funVector(b, c));
    float third = lenVector(funVector(c, d));
    return first + second + third;
}
float atriangle(point a, point b, point c, point d) // По формуле Герона
{
    float p = ptriangle(a, b, c, d) / 2;
    float ta = lenVector(funVector(a, b));
    float tb = lenVector(funVector(b, c));
    float tc = lenVector(funVector(c, d));
    return sqrt(p * (p - ta) * (p - tb) * (p - tc));
}