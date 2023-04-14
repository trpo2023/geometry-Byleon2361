#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <libgeometry/exception.h>
#include <libgeometry/geo.h>
#include <libgeometry/intersection.h>

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
bool checkIntersectionTriangleAndTriangle(segment ab, segment cd)
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
bool checkIntersectionCircleAndTriangle(
        point o, int rad, point a, point b, point c)
{
    vector first = findVector(o, a);
    vector second = findVector(o, b);
    vector third = findVector(o, c);
    double firstLength = lengthVector(first);
    double secondLength = lengthVector(second);
    double thirdLength = lengthVector(third);
    if (firstLength <= rad)
        return true;
    if (secondLength <= rad)
        return true;
    if (thirdLength <= rad)
        return true;

    return false;
}
bool checkIntersectionCircleAndCirle(
        point firstCenter, int firstRad, point secomdCenter, int secondRad)
{
    vector vec = findVector(firstCenter, secomdCenter);
    double vecLength = lengthVector(vec);
    if (vecLength <= firstRad + secondRad)
        return true;

    return false;
}
// В целом
void checkIntersection(figure firstFigure, int countFigures, figure* allFigures)
{
    figure secondFigure;
    bool intersection;
    int secondType;
    printf("Intersect: \n");
    for (int i = 0; i < countFigures; i++) {
        secondFigure = allFigures[i];
        secondType = secondFigure.type;
        if (firstFigure.type == CIRCLE && secondType == CIRCLE) {
            point firstO;
            double firstRad = 0;
            sscanf(secondFigure.name,
                   "circle(%lf %lf, %lf)",
                   &firstO.x,
                   &firstO.y,
                   &firstRad);
            point secondO;
            double secondRad = 0;
            sscanf(secondFigure.name,
                   "circle(%lf %lf, %lf)",
                   &secondO.x,
                   &secondO.y,
                   &secondRad);
            if (checkIntersectionCircleAndCirle(
                        firstO, firstRad, secondO, secondRad))
                printf("    %d. %s\n", secondFigure.number, secondFigure.name);
        } else if (firstFigure.type == TRIANGLE && secondType == CIRCLE) {
            point a;
            point b;
            point c;
            point d;
            sscanf(firstFigure.name,
                   "triangle(%lf %lf, %lf %lf, %lf %lf, %lf %lf)",
                   &a.x,
                   &a.y,
                   &b.x,
                   &b.y,
                   &c.x,
                   &c.y,
                   &d.x,
                   &d.y);

            point o;
            double rad = 0;
            sscanf(secondFigure.name, "circle(%lf %lf, %lf)", &o.x, &o.y, &rad);
            if (checkIntersectionCircleAndTriangle(o, rad, a, b, c))
                printf("    %d. %s\n", secondFigure.number, secondFigure.name);
        } else if (firstFigure.type == CIRCLE && secondType == TRIANGLE) {
            point a;
            point b;
            point c;
            point d;
            sscanf(secondFigure.name,
                   "triangle(%lf %lf, %lf %lf, %lf %lf, %lf %lf)",
                   &a.x,
                   &a.y,
                   &b.x,
                   &b.y,
                   &c.x,
                   &c.y,
                   &d.x,
                   &d.y);

            point o;
            double rad = 0;
            sscanf(firstFigure.name, "circle(%lf %lf, %lf)", &o.x, &o.y, &rad);
            if (checkIntersectionCircleAndTriangle(o, rad, a, b, c))
                printf("    %d. %s\n", secondFigure.number, secondFigure.name);
        } else if (firstFigure.type == TRIANGLE && secondType == TRIANGLE) {
            point a;
            point b;
            point c;
            point d;
            sscanf(firstFigure.name,
                   "triangle(%lf %lf, %lf %lf, %lf %lf, %lf %lf)",
                   &a.x,
                   &a.y,
                   &b.x,
                   &b.y,
                   &c.x,
                   &c.y,
                   &d.x,
                   &d.y);
            segment firstFigureFirstSegment = {a, b};
            segment firstFigureSecondSegment = {b, c};
            segment firstFigureThirdSegment = {c, d};
            sscanf(secondFigure.name,
                   "triangle(%lf %lf, %lf %lf, %lf %lf, %lf %lf)",
                   &a.x,
                   &a.y,
                   &b.x,
                   &b.y,
                   &c.x,
                   &c.y,
                   &d.x,
                   &d.y);
            segment secondFigureFirstSegment = {a, b};
            segment secondFigureSecondSegment = {b, c};
            segment secondFigureThirdSegment = {c, d};

            if (checkIntersectionTriangleAndTriangle(
                        firstFigureFirstSegment, secondFigureFirstSegment))
                intersection = true;
            else if (checkIntersectionTriangleAndTriangle(
                             firstFigureFirstSegment,
                             secondFigureSecondSegment))
                intersection = true;
            else if (checkIntersectionTriangleAndTriangle(
                             firstFigureFirstSegment, secondFigureThirdSegment))
                intersection = true;
            else if (checkIntersectionTriangleAndTriangle(
                             firstFigureSecondSegment,
                             secondFigureFirstSegment))
                intersection = true;
            else if (checkIntersectionTriangleAndTriangle(
                             firstFigureSecondSegment,
                             secondFigureSecondSegment))
                intersection = true;
            else if (checkIntersectionTriangleAndTriangle(
                             firstFigureSecondSegment,
                             secondFigureThirdSegment))
                intersection = true;
            else if (checkIntersectionTriangleAndTriangle(
                             firstFigureThirdSegment, secondFigureFirstSegment))
                intersection = true;
            else if (checkIntersectionTriangleAndTriangle(
                             firstFigureThirdSegment,
                             secondFigureSecondSegment))
                intersection = true;
            else if (checkIntersectionTriangleAndTriangle(
                             firstFigureThirdSegment, secondFigureThirdSegment))
                intersection = true;
            else
                intersection = false;

            if (intersection)
                printf("    %d. %s\n", secondFigure.number, secondFigure.name);
            intersection = false;
        }
    }
}