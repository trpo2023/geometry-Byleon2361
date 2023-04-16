#pragma once
#include "geo.h"
enum { CIRCLE = 0, TRIANGLE };
// Если найдена ошибка,то функции возвращают true
bool checkBracketException(char* string, char* output);
bool checkValueException(char* string, char* output);
bool checkEndSymException(char* string, char* output);
bool checkNameException(char* string, int* action);
char* findEnd(char* string);
bool drawException(point a, point d);
bool checkRadException(int rad);
bool checkLineException(point a, point b, point c);