#include <stdio.h>
#include <math.h>
#define PI 3.14
typedef struct Point 
{
    int x;
    int y;
} point;
typedef struct Vector 
{
    int a;
    int b;
} vector;
vector funVector(point first, point second)
{
    vector res = {(second.x - first.x),(second.y - first.y)};
    return res;
}
double lenVector(vector vec)
{
    return sqrt(vec.a * vec.a + vec.b * vec.b);
}
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
    float first = lenVector(funVector(a,b));
    float second = lenVector(funVector(b,c));
    float third = lenVector(funVector(c,d));
    return first + second + third;
}
float striangle(point a,point b, point c, point d) // По формуле Герона
{
    float p = ptriangle(a,b,c,d) / 2;
    float a = lenVector(funVector(a,b));
    float b = lenVector(funVector(b,c));
    float c = lenVector(funVector(c,d));
    return sqrt(p*(p-a)*(p-b)*(p-c));
} 


int main()
{
    
    point center = {0,0};
    float rad = 3;
    //printf("P = %f; S = %f\n", pcircle(center, rad), acircle(center,rad));
    
    point a = {2,3};
    point b = {5,5};
    point c = {9,7};
    //printf("P = %f; S=%f", ptriangle(a,b,c,a), atriandle(a,b,c,a)); 
    printf("%d,%d\n",funVector(a,b).a,funVector(a,b).b);
    printf("%f",lenVector(funVector(a,b)));
    return 0;
}