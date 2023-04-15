#pragma once
#include "geo.h"
enum { CIRCLE = 0, TRIANGLE };
bool checkBracket(char* string, char* output);
bool checkValue(char* string, char* output);
bool checkEndSym(char* string, char* output);
bool checkName(char* string, int* action);
char* findEnd(char* string);
bool dontDraw(point a, point d);
bool checkRad(int rad);
bool lineException(point a, point b, point c);