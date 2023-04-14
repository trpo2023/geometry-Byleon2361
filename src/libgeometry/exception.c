#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"
#include "geo.h"
// Ошибки ввода данных
void checkBracket(char* string)
{
    char* end = findEnd(string);
    if (end == NULL) {
        printf("Error at column %ld: expected ')' \n", strlen(string) - 1);
        exit(EXIT_FAILURE);
    }
}
void checkValue(char* string)
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
            printf("Error at column %d: expected '<double>'\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }
}
void checkEndSym(char* string)
{
    char* end = findEnd(string);
    for (int i = 0; i < strlen(end); i++) {
        if (!(end[i + 1] == ' ' || end[i + 1] == '\000'
              || end[i + 1] == '\n')) {
            printf("Error at column %ld: unexpected token\n", strlen(string));
            exit(EXIT_FAILURE);
        }
    }
}
void checkName(char* string, int* action)
{
    if ((strstr(string, "circle(")
         != NULL)) // strcmp - сравнивает строки, strstr - содержится ли строка
    {
        *action = CIRCLE;

    } else if ((strstr(string, "triangle(") != NULL)) {
        *action = TRIANGLE;

    } else if ((strstr(string, "q") != NULL)) {
    } else {
        printf("Error at column 0: expected 'circle', 'triangle' or "
               "'polygon' \n");
        exit(EXIT_FAILURE);
    }
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
void lineException(point a, point b, point c)
{
    if (((a.x == b.x) && (b.x == c.x)) || ((a.y == b.y) && (b.y == c.y))) {
        puts("Failed to construct a triangle. All points on the same "
             "line\n");
        exit(EXIT_FAILURE);
    }
}
void dontDraw(point a, point d)
{
    if ((a.x != d.x) || (a.y != d.y)) {
        puts("Failed to construct a triangle. A and d must match\n");
        exit(EXIT_FAILURE);
    }
}

// Ошибки круга
void checkRad(int rad)
{
    if (rad < 0) {
        puts("Radius cannot be negative\n");
        exit(EXIT_FAILURE);
    }
}
