#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"
#include "geo.h"
// Ошибки ввода данных
bool check = false;
bool checkBracketException(char* string, char* output)
{
    char* end = findEnd(string);
    if (end == NULL) {
        sprintf(output,
                "Error at column %ld: expected ')' \n",
                strlen(string) - 1);
        return true;
    }
    return false;
}
bool checkValueException(char* string, char* output)
{
    char* start;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '(') {
            start = &string[i];
        }
    }
    char* end = findEnd(string);
    for (int i = 0; i < end - start; i++) {
        if (!(start[i + 1] == ' ' || start[i + 1] == ',' || start[i + 1] == '.'
              || start[i + 1] == ')'
              || ((int)start[i + 1] >= (int)'0'
                  && (int)start[i + 1] <= (int)'9'))) {
            sprintf(output, "Error at column %d: expected '<double>'\n", i + 1);
            return true;
        }
    }
    return false;
}
bool checkEndSymException(char* string, char* output)
{
    char* end = findEnd(string);
    for (int i = 0; i < strlen(end); i++) {
        if (!(end[i + 1] == ' ' || end[i + 1] == '\000'
              || end[i + 1] == '\n')) {
            printf(output,
                   "Error at column %ld: unexpected token\n",
                   strlen(string));
            return true;
        }
    }
    return false;
}
bool checkNameException(char* string, int* action)
{
    if ((strstr(string, "circle(")
         != NULL)) // strcmp - сравнивает строки, strstr - содержится ли строка
    {
        *action = CIRCLE;

    } else if ((strstr(string, "triangle(") != NULL)) {
        *action = TRIANGLE;

    } else if ((strstr(string, "q") != NULL)) {
        exit(EXIT_SUCCESS);
    } else {
        return true;
    }
    return false;
}
char* findEnd(char* string)
{
    char* end = NULL;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == ')') {
            end = &string[i];
        }
    }
    return end;
}

// Ошибки треугольника
bool checkLineException(point a, point b, point c)
{
    if (((a.x == b.x) && (b.x == c.x)) || ((a.y == b.y) && (b.y == c.y)))
        return true;
    if((a.x == c.y) && (b.x == b.y) && (c.x == a.y)) // Диагональ
	true;
	
    return false;
}
bool drawException(point a, point d)
{
    if ((a.x != d.x) || (a.y != d.y))
        return true;

    return false;
}

// Ошибки круга
bool checkRadException(double rad)
{
    if (rad < 0)
        return true;

    return false;
}
