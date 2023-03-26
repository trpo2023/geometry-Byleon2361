#ifndef GEO_H
#define GEO_H
typedef struct Point {
    int x;
    int y;
} point;
typedef struct Vector {
    int a;
    int b;
} vector;

vector funVector(point first, point second);
double lenVector(vector vec);
float pcircle(point center, double rad);
float acircle(point center, double rad);
float ptriangle(point a, point b, point c, point d);
float atriangle(point a, point b, point c, point d);

#endif