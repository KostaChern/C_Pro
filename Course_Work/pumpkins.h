#ifndef PUMPKINS_H_
#define PUMPKINS_H_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <Windows.h>

#define MAX_X 14 // row
#define MAX_Y 21 // col

typedef struct pumpkins_t
{
    int x;                      // Координаты тыквы
    int y;                      // Координаты тыквы
    int number;                 // Номер тыквы
    int state;                  // Состояние тыквы 
    struct pumpkins_t *next;    
} pumpkins_t;

int getRand();      // Вспомогательная функция
void insertPumpkin(pumpkins_t **head, int x, int y, int count); // Добавление Тыквы в список
void initPumpkins(pumpkins_t **head);                           // Инициализация тыквы
int findPumpkinState(pumpkins_t *head, int x, int y);           // Проверка состояния тыквы
pumpkins_t *findPumpkin(pumpkins_t *head, int number);          // Поиск тыквы в списке по номеру
pumpkins_t *findPumpkinPos(pumpkins_t *head, int x, int y);     // Поиск тыквы в списке по координатам
void ripening(pumpkins_t **head);                               // Смена статуса тыквы 
pumpkins_t *getRipePumpkin(pumpkins_t *head);                   // Поиск созревшей тыквы в списке 

#endif