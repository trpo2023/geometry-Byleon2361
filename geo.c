#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

float pcircle(point center, double rad)
{
    return 2 * M_PI * rad;
}
float acircle(point center, double rad)
{
    return M_PI * rad * rad;
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
void Exception(char* string)
{
    int length = strlen(string);
    char* end;
    char* start;
    for(int i = 0 ; i < length; i++ )
    {
         if(string[i] == ')')
        {
            end = &string[i];
        }
        if(string[i] == '(')
        {
            start = &string[i];
        }
    }        
    if(end == NULL)
    {
        printf("Error at column %d: expected ')' \n", length - 1); 
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < strlen(end);i++) 
    {
        if(!(end[i+1] == ' ' || end[i+1] == '\000' ))
        {
            printf("Error at column %d: unexpected token\n", length );
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < end - start;i++) 
    {
        if(!(start[i+1] == ' ' || start[i+1] == ',' || start[i+1] == '.' || start[i+1] == ')'  || ((int)start[i+1] >= (int)'0' && (int)start[i+1] <= (int)'9')))
        {
            printf("Error at column %d: expected '<double>'\n", i+1);
            exit(EXIT_FAILURE);
        }
    }
      
}

int main()
{
    puts("Введите название фигуры и передайте значения по образцу:\n\n\
Object = 'circle' '(' Point ',' Number ')'\n\
| 'triangle' '(' '(' Point ',' Point ',' Point ',' Point ')' ')'\n\
| 'polygon' '(' '(' Point ',' Point ',' Point {',' Point } ')' ')'\n\n\
Пример: circle(0 0, 1.5)\n\n\
Для того, чтобы выйти введите q.\n");
    char string[64];
    do
    {
        gets(string);
        if((strstr(string, "circle(") != NULL)) //strcmp - сравнивает строки, strstr - содержится ли строка 
        {
    	    point a;
    	    double rad = 0;
    	    Exception(string);
            sscanf(string, "circle(%d %d, %lf)", &a.x, &a.y, &rad);
            printf("Done\n");
            printf("Perimetr: %.3f, Area: %.3f\n" ,pcircle(a,rad), acircle(a,rad));
        }  
        else if((strstr(string, "triangle(") != NULL)) 
        {
    	    point a;
    	    point b;
    	    point c;
    	    point d;
    	    Exception(string); 
            sscanf("triangle(%d %d, %d %d, %d %d, %d %d)", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
            printf("Done");
            printf("Perimetr: %f, Area: %f\n", ptriangle(a,b,c,d), atriangle(a,b,c,d));
            
        }
        else
        {
            if(strcmp(string, "q"))
            {
                printf("Error at column 0: expected 'circle', 'triangle' or 'polygon' \n"); 
            }
        }   
    }while(strcmp(string, "q"));
    return 0;
}