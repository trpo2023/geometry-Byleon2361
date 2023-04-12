#include <libgeometry/geo.h>
#include <math.h>
#include <stdbool.h>
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

bool rangeIntersection(
        double firstStart,
        double firstEnd,
        double secondStart,
        double secondEnd) // Проверяет содержатся ли проекции отрезка
                          // в другой проекции
{
    double temp;
    if (firstStart > firstEnd) {
        temp = firstEnd;
        firstEnd = firstStart;
        firstStart = temp;
    }
    if (secondStart > secondEnd) {
        temp = secondEnd;
        secondEnd = secondStart;
        secondStart = temp;
    }

    if (fmax(firstStart, secondStart) <= fmin(firstEnd, secondEnd))
        return true;
    else
        return false;
}
bool boundingBox(
        segment firstSegment,
        segment secondSegment) // Попарное пересечени проекци на ось x и y
{
    bool xRangeIntersection = rangeIntersection(
            firstSegment.start.x,
            firstSegment.end.x,
            secondSegment.start.x,
            secondSegment.end.x);
    bool yRangeIntersection = rangeIntersection(
            firstSegment.start.y,
            firstSegment.end.y,
            secondSegment.start.y,
            secondSegment.end.y);
    if (xRangeIntersection && yRangeIntersection)
        return true;
    else
        return false;
}
bool checkIntersection(segment ab, segment cd)
{
    if (!boundingBox(ab, cd))
        return false;

    vector vAB = findVector(ab.start, ab.end);
    vector vAC = findVector(ab.start, cd.start);
    vector vAD = findVector(ab.start, cd.end);

    vector vCD = findVector(cd.start, cd.end);
    vector vCA = findVector(cd.start, ab.start);
    vector vCB = findVector(cd.start, ab.end);

    double d1 = vectorCrossProduct(vAB, vAC);
    double d2 = vectorCrossProduct(vAB, vAD);

    double d3 = vectorCrossProduct(vCD, vCA);
    double d4 = vectorCrossProduct(vCD, vCB);

    if (((d1 <= 0 && d2 >= 0) || (d1 >= 0 && d2 <= 0))
        && ((d3 <= 0 && d4 >= 0) || (d3 >= 0 && d4 <= 0)))
        return true;
    else
        return false;
}
double vectorCrossProduct(vector vector1, vector vector2)
{
    return vector1.a * vector2.b - vector2.a * vector1.b;
}