#pragma once
#include "geo.h"
enum { CIRCLE = 0, TRIANGLE };
void checkBracket(char* string);
void checkValue(char* string);
void checkEndSym(char* string);
void checkName(char* string, int* action);
char* findEnd(char* string);
void dontDraw(point a, point d);
void checkRad(int rad);