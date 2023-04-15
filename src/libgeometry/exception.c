#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"
#include "geo.h"
// Ошибки ввода данных
bool check = false;
bool checkBracket(char* string, char* output)
{
    char* end = findEnd(string);
    if (end == NULL) {
        sprintf(output,
                "Error at column %ld: expected ')' \n",
                strlen(string) - 1);
        return false;
    }
    return true;
}
bool checkValue(char* string, char* output)
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
            return false;
        }
    }
    return true;
}
bool checkEndSym(char* string, char* output)
{
    char* end = findEnd(string);
    for (int i = 0; i < strlen(end); i++) {
        if (!(end[i + 1] == ' ' || end[i + 1] == '\000'
              || end[i + 1] == '\n')) {
            printf(output,
                   "Error at column %ld: unexpected token\n",
                   strlen(string));
            return false;
        }
    }
    return true;
}
bool checkName(char* string, int* action)
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
        return false;
    }
    return true;
}
char* findEnd(char* string)
{
    char* end;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == ')') {
            end = &string[i];
        }
    }
    return end;
}

// Ошибки треугольника
bool lineException(point a, point b, point c)
{
    if (((a.x == b.x) && (b.x == c.x)) || ((a.y == b.y) && (b.y == c.y)))
        return false;

    return true;
}
bool dontDraw(point a, point d)
{
    if ((a.x != d.x) || (a.y != d.y))
        return false;

    return true;
}

// Ошибки круга
bool checkRad(int rad)
{
    if (rad < 0)
        return false;

    return true;
}
