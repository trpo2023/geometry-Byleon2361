#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/exception.h>
#include <libgeometry/geo.h>

#define MAXSIZESEGMENTS 100
#define MAXSIZEFIGURES 100

segment allSegments[MAXSIZESEGMENTS];
figure allFigures[MAXSIZEFIGURES];
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
    bool intersection = false;
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

            printf("%d. %s\n Perimetr circle: %.3f\n Area circle: %.3f\n",
                   number++,
                   string,
                   perimeterCircle(o, rad),
                   areaCircle(o, rad));

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

            figure newFigure;
            newFigure.number = ++number;
            strcpy(newFigure.name, string);
            newFigure.perimeter = perimeterTriangle(a, b, c, d);
            newFigure.area = areaTriangle(a, b, c, d);

            printf("%d. %s\nPerimetr triangle: %f\n Area triangle: %f\n",
                   newFigure.number,
                   newFigure.name,
                   newFigure.perimeter,
                   newFigure.area);

            segment first = {a, b};
            segment second = {b, c};
            segment third = {c, d};
            if (count == 0) {
                allSegments[0] = first;
                allSegments[1] = second;
                allSegments[2] = third;
                count = 3;
                continue;
            }
            for (int i = 0; i < count; i++) {
                if (checkIntersection(first, allSegments[i]))
                    intersection = true;
                if (checkIntersection(second, allSegments[i]))
                    intersection = true;
                if (checkIntersection(third, allSegments[i]))
                    intersection = true;
            }
            count += 3;
            allSegments[count - 2] = first;
            allSegments[count - 1] = second;
            allSegments[count] = third;
            if (intersection)
                printf("Пересекается");
            intersection = false;

            break;
        default:
            puts("Что-то пошло не так");
            break;
        }
    } while ((strcmp(string, "q")) && (!feof(f)));
    return 0;
}