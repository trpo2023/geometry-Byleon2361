#include <stdio.h>
#include <math.h>
#include <string.h>
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
float atriangle(point a,point b, point c, point d) // По формуле Герона
{
    float p = ptriangle(a,b,c,d) / 2;
    float ta = lenVector(funVector(a,b));
    float tb = lenVector(funVector(b,c));
    float tc = lenVector(funVector(c,d));
    return sqrt(p*(p-ta)*(p-tb)*(p-tc));
    
}


int main()
{
    char string[64];
    gets(string);
    char* suffix;
    suffix = &string[12];
    printf("suffix: %s", suffix);
    if(string[strlen(string) - 1] != ')')
    {
	printf("Error at column %d: expected ')' ", strlen(string)-1);
    }
    
    if((strstr(string, "circle(") != NULL) && (string[strlen(string) - 1] == ')')) //strcmp - сравнивает строки, strstr - содержится ли строка 
    {
	printf("Done");
	point a = {string[7], string[9]};
	//pcircle(a, );
	//acircle(a, );
    }
    else if((strstr(string, "triangle(") != NULL) && (string[strlen(string) - 1] == ')')) //strcmp - сравнивает строки, strstr - содержится ли строка.
    {
	printf("Done");
	//ptriangle();
	//atriandle();
    }
    else if((strstr(string, "polygon(") != NULL) && (string[strlen(string) - 1] == ')')) //strcmp - сравнивает строки, strstr - содержится ли строка.
    {
	printf("Done");
    }
    else
    {
	printf("Error at column 0: expected 'circle', 'triangle' or 'polygon' ");
    }
    /*
    point center = {0,0};
    float rad = 3;
    //printf("P = %f; S = %f\n", pcircle(center, rad), acircle(center,rad));
    
    point a = {2,3};
    point b = {5,5};
    point c = {9,7};
    //printf("P = %f; S=%f", ptriangle(a,b,c,a), atriandle(a,b,c,a)); 
    printf("%d,%d\n",funVector(a,b).a,funVector(a,b).b);
    printf("%f",lenVector(funVector(a,b))); */
    
    return 0;
}