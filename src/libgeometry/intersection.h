#pragma once
#include "geo.h"
// Если есть пересечения возвращает true
bool rangeIntersection(
        double firstStart,
        double firstEnd,
        double secondStart,
        double secondEnd);
bool boundingBox(segment firstSegment, segment secondSegment);
bool checkIntersectionTriangleAndTriangle(segment ab, segment cd);
double vectorCrossProduct(vector vector1, vector vector2);
bool checkIntersectionCircleAndTriangle(
        point o, int rad, point a, point b, point c);
bool checkIntersectionCircleAndCirle(
        point firstCenter, int firstRad, point secomdCenter, int secondRad);
void checkIntersection(
        figure firstFigure, int countFigures, figure* allFigures);