#include <stdio.h>
#include <stdlib.h>
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
void Exception(char* string,int number , int *rad, point *a, point *b, point *c, point *d)// number - количесвто аргументов
{
        int length = strlen(string);
        char* end;
        char* start;
        for(int i; i < length; i++ )
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
            
        if(end == NULL)// Проверка )
        {
            printf("Error at column %d: expected ')' \n", (int)(end-string)); //разность указатлей возвращает их длину
	    exit(EXIT_FAILURE);
        }
        
        for(int i = 0; i < strlen(end); i++) // Проверка на конеченые символы
        {
            if(((int)end[i+1] != (int)'\0') || ((int)end[i+1] != (int)' '))
            {
                printf("Error at column %d: unexpected token\n",(int)(end-string)+i+1 );
                exit(EXIT_FAILURE);
            }
        }
        int j = 0;
        for(int i = 0;(i < end - start) && (j < number);i++)
        {
    	        if(start[i+1] == ' ' ||start[i+1] == ','|| start[i+1] == '.'||start[i+1] == ')')
                {
                    continue;
                }

                if( ((int)start[i+1] > (int)'0') && ((int)start[i+1] < (int)'9') )
                {
                    if(a->x == NULL)
                    {
                        a->x = atoi(start[i+1]);
                    }
                    else if (a->y== NULL)
                    {
                        a->y = atoi(start[i+1]);
		    }
		    else
		    {
			*rad = atof(start[i+1]);
		    }
                }
                else
                {
                    printf("Error at column %d: expected '<double>'\n", i+1);
                    exit(EXIT_FAILURE);
                }
        }
}

int main()
{
    char string[64];
    do
    {
        gets(string);
        if((strstr(string, "circle(") != NULL)) //strcmp - сравнивает строки, strstr - содержится ли строка 
        {
    	    point a;
    	    double rad;
    	    Exception(string, 3, &rad, &a, NULL, NULL, NULL);
            printf("Done\n");
            printf("Perimetr: %f, Area: %f\n" ,pcircle(a,rad), acircle(a,rad));
        }
        
        else if((strstr(string, "triangle(") != NULL)) //strcmp - сравнивает строки, strstr - содержится ли строка.
        {
    	    point a;
    	    point b;
    	    point c;
    	    point d;
    	    Excaption(string, 8, NULL, a, b, c, d); // 8 - предполагаемое количесвто символов
            printf("Done");
            printf("Perimetr: %f, Area: %f\n", ptriangle(a,b,c,d), atriangle(a,b,c,d));
            
        }
	//else if((strstr(string, "polygon(") != NULL)) //strcmp - сравнивает строки, strstr - содержится ли строка.
        //{
    //        printf("Done");
    //    }
        else
        {
            printf("Error at column 0: expected 'circle', 'triangle' or 'polygon' ");
        }
        
    }while(string != "q");
    return 0;
}