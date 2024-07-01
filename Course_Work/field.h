#ifndef FIELD_H_
#define FIELD_H_

#include "pumpkins.h"
#include "drone.h"
#include <ctype.h>

#define MAX_X 14// row
#define MAX_Y 21 // col
#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE
#define CYAN FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define YELLOW FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define WHITE FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define MAGENTA FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE

void initField(char matrix[MAX_X][MAX_Y]); // Отрисовка границ поля
void printField(char matrix[MAX_X][MAX_Y], pumpkins_t *list, node *droneList, drone_t *drone1); // Вывод поля на экран
#endif