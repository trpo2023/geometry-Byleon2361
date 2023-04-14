#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/exception.h>
#include <libgeometry/geo.h>
#include <libgeometry/intersection.h>

#define MAXSIZESEGMENTS 100
#define MAXSIZEFIGURES 100

segment allSegments[MAXSIZESEGMENTS];
figure allFigures[MAXSIZEFIGURES];
int countFigures = 0;
int countSegments = 0;
// Сделать пересечение фигур
// Добавить скобки для треугольника
// Покрыть тестами
int main(int argc, char* argv[])
{
    printf("%d", argc);
    const char* in_file_name = argv[1];
    FILE* f;
    if (argc == 2) {
        f = fopen(in_file_name, "r");
    }

    int count = 0;
    int number = 0;
    figure newFigure;
    puts("Введите название фигуры и передайте значения по образцу:\n\n\
Object = 'circle' '(' Point ',' Number ')'\n\
| 'triangle' '(' '(' Point ',' Point ',' Point ',' Point ')' ')'\n\n\
Пример: circle(0 0, 1.5)\n\n\
Для того, чтобы выйти введите q.\n");
    char string[64];
    do {
        if (argc == 2)
            fgets(string, 64, f);
        else
            fgets(string, 64, stdin);
        int name;

        checkName(string, &name);
        checkBracket(string);
        checkValue(string);
        checkEndSym(string);
        switch (name) {
        case CIRCLE:
            point o;
            double rad = 0;
            sscanf(string, "circle(%lf %lf, %lf)", &o.x, &o.y, &rad);
            checkRad(rad);

            newFigure.number = ++number;
            strcpy(newFigure.name, string);
            newFigure.perimeter = perimeterCircle(o, rad);
            newFigure.area = areaCircle(o, rad);
            newFigure.type = name;

            printf("%d. %s\n Perimetr circle: %.3f\n Area circle: %.3f\n",
                   number++,
                   string,
                   perimeterCircle(o, rad),
                   areaCircle(o, rad));
            checkIntersection(newFigure, countFigures, allFigures);
            break;
        case TRIANGLE:

            point a;
            point b;
            point c;
            point d;
            sscanf(string,
                   "triangle(%lf %lf, %lf %lf, %lf %lf, %lf %lf)",
                   &a.x,
                   &a.y,
                   &b.x,
                   &b.y,
                   &c.x,
                   &c.y,
                   &d.x,
                   &d.y);
            dontDraw(a, d);
            lineException(a, b, c);

            newFigure.number = ++number;
            strcpy(newFigure.name, string);
            newFigure.perimeter = perimeterTriangle(a, b, c, d);
            newFigure.area = areaTriangle(a, b, c, d);
            newFigure.type = name;

            printf("%d. %s\nPerimetr triangle: %f\n Area triangle: %f\n",
                   newFigure.number,
                   newFigure.name,
                   newFigure.perimeter,
                   newFigure.area);
            checkIntersection(newFigure, countFigures, allFigures);
            allFigures[countFigures++] = newFigure;

            break;
        default:
            puts("Что-то пошло не так");
            break;
        }
    } while ((strcmp(string, "q")) && (!feof(f)));
    return 0;
}