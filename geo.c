#include <stdio.h>
#define PI 3.14
typedef struct Point 
{
    int x;
    int y;
} point;

float pcircle(point center, int rad)
{
    return 2 * PI * rad;
}
float acircle(point center, int rad)
{
    return PI * rad * rad;
}

float ptriangle(point a, point b,point c, point d)
{
    res = 
    return res;
}
float striangle(point a,point b, point c, point d)
{
    res
    return res;
}
int main()
{
    point center = {0,0};
    float rad = 3;
    printf("P = %f; S = %f\n", pcircle(center, rad), acircle(center,rad));
    
    point a = {2,3};
    point b = {3,4};
    point c = {5,5};
    printf("P = %f; S=%f", ptriangle(a,b,c,a), atriandle(a,b,c,a));
    return 0;
}