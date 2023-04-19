#include "ctest.h"

#include <libgeometry/exception.h>
#include <libgeometry/geo.h>
#include <libgeometry/intersection.h>

// geo
CTEST(GEOMETRY_MATH, VECTOR_LENGTH)
{
    vector vec = {-3, 4};
    ASSERT_DBL_NEAR((double)5.0, lengthVector(vec));
}
CTEST(GEOMETRY_MATH, PERIMETER_CIRCLE)
{
    point o = {0, 0};
    ASSERT_DBL_NEAR_TOL((double)31.4159265, perimeterCircle(o, 5), 0.0001);
}
CTEST(GEOMETRY_MATH, AREA_CIRCLE)
{
    point o = {0, 0};
    ASSERT_DBL_NEAR_TOL((double)78.539816, areaCircle(o, 5), 0.0001);
}
CTEST(GEOMETRY_MATH, PERIMETER_TRIANGLE)
{
    point a = {0, 0};
    point b = {-1, -1};
    point c = {-2, 0};
    point d = {0, 0};
    ASSERT_DBL_NEAR_TOL(
            (double)4.828427, perimeterTriangle(a, b, c, d), 0.0001);
}
CTEST(GEOMETRY_MATH, AREA_TRIANGLE)
{
    point a = {0, 0};
    point b = {-1, -1};
    point c = {-2, 0};
    point d = {0, 0};
    ASSERT_DBL_NEAR_TOL((double)1.0, areaTriangle(a, b, c, d), 0.0001);
}

// Exception
CTEST(GEOMETRY_EXCEPTION, CHECK_BRACKET_EXCEPTION)
{
    char output[100];
    char* string = "circle(1 2, 3.1";
    ASSERT_EQUAL(true, checkBracketException(string, output));
}
CTEST(GEOMETRY_EXCEPTION, CHECK_VALUE_EXCEPTION)
{
    char* string = "circle(x1 2, 3.0)";
    char output[100];
    ASSERT_EQUAL(true, checkValueException(string, output));
}
CTEST(GEOMETRY_EXCEPTION, CHECK_END_SYMBOL_EXCEPTION)
{
    char* string = "circle(1.0 2.1, 3) 123";
    char output[100];
    ASSERT_EQUAL(true, checkEndSymException(string, output));
}
CTEST(GEOMETRY_EXCEPTION, CHECK_NAME_EXCEPTION)
{
    char* string = "circlee(1.0 2.0, 3)";
    int action = CIRCLE;
    ASSERT_EQUAL(true, checkNameException(string, &action));
}
CTEST(GEOMETRY_EXCEPTION, CHECK_DRAW_EXCEPTION)
{
    point a = {-1, -1};
    point d = {-1, -1};
    ASSERT_EQUAL(false, drawException(a, d));
    a.x = 1;
    a.y = 0;
    d.x = 0;
    d.y = 1;
    ASSERT_EQUAL(true, drawException(a, d));
}
CTEST(GEOMETRY_EXCEPTION, CHECK_RADIUS_EXCEPTION)
{
    double rad = 2;
    ASSERT_EQUAL(false, checkRadException(rad));
    rad = -2;
    ASSERT_EQUAL(true, checkRadException(rad));
}
CTEST(GEOMETRY_EXCEPTION, CHECK_LINE_EXCEPTION)
{
    point a = {0, -1};
    point b = {0, -2};
    point c = {0, -3};
    ASSERT_EQUAL(true, checkLineException(a, b, c));
    point d = {-1, 0};
    point e = {-2, 0};
    point f = {-3, 0};
    ASSERT_EQUAL(true, checkLineException(d, e, f));
}

// Intersection
CTEST(GEOMETRY_INERSECTION, CHECK_INTERSECTION_CIRCLE_AND_TRIANGLE)
{
    point firstO = {0, 0};
    double firstRad = 2;
    point a = {2, 0};
    point b = {3, 1};
    point c = {4, 0};
    ASSERT_EQUAL(
            true,
            checkIntersectionCircleAndTriangle(firstO, firstRad, a, b, c));
    point secondO = {0, 0};
    double secondRad = 1;
    point d = {2, 0};
    point e = {3, 1};
    point f = {4, 0};
    ASSERT_EQUAL(
            false,
            checkIntersectionCircleAndTriangle(secondO, secondRad, d, e, f));
}
CTEST(GEOMETRY_INERSECTION, CHECK_INTERSECTION_CIRCLE_AND_CIRCLE)
{
    point firstO = {0, 0};
    double firstRad = 2;
    point secondO = {0, 4};
    double secondRad = 2;
    ASSERT_EQUAL(
            true,
            checkIntersectionCircleAndCirle(
                    firstO, firstRad, secondO, secondRad));
    point firstO2 = {0, 0};
    double firstRad2 = 2;
    point secondO2 = {0, 5};
    double secondRad2 = 2;
    ASSERT_EQUAL(
            false,
            checkIntersectionCircleAndCirle(
                    firstO2, firstRad2, secondO2, secondRad2));
}
CTEST(GEOMETRY_INERSECTION, CHECK_INTERSECTION_TRIANGLE_AND_TRIANGLE)
{
    point a = {0, 0};
    point b = {2, 0};
    point c = {2, 0};
    point d = {1, 1};
    segment ab = {a, b};
    segment cd = {c, d};
    ASSERT_EQUAL(true, checkIntersectionTriangleAndTriangle(ab, cd));
    point x = {0, 0};
    point y = {1, 1};
    point e = {1, 0};
    point f = {2, 0};
    segment xy = {x, y};
    segment ef = {e, f};
    ASSERT_EQUAL(false, checkIntersectionTriangleAndTriangle(xy, ef));
}