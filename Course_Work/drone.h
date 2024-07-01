#ifndef DRONE_H_
#define DRONE_H_

#include "pumpkins.h"


#define MAX_X 14 // row
#define MAX_Y 21 // col
#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE
#define CYAN FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define YELLOW FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define WHITE FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define MAGENTA FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define STOP 5



typedef struct drone_t
{
    int x;                  // Координата дрона в настоящее время
    int y;                  // Координата дрона в настоящее время
    int targetX;            // Координата цели дрона 
    int targetY;            // Координата цели дрона 
    int defTargetX;         // Координата зоны выгрузки дрона 
    int defTargetY;         // Координата зоны выгрузки дрона 
    int direction;          // Текущее направление движения дрона
    char color;             // Цвет дрона
    int atWork;             // Состояние дрона
    struct basket_t *basket;// Корзина для урожая
    int tsize;              // Длинна 
} drone_t;

typedef struct basket_t
{
    int x;                  // Координаты корзины
    int y;                  // Координаты корзины
    int isEmpty;            // Состояние корзины (свободна или загружена)
} basket_t;

typedef struct node         // Список для автоматических дронов
{
    drone_t *drone;
    int number;
    struct node *next;
} node;

typedef struct freeColor_t  // Список для определения доступности цвета
{
    WORD color;
    int state;
    struct freeColor_t *next;
}freeColor_t;


void initFreeColor(freeColor_t **freeColor);    // Заполнение списка цветов
void printColor(freeColor_t *list);             // Печать списка цветов
void deleteNode(node **head, node *toRemove);   // Удаление автоматического дрона из списка
node *findNode(node *head, char color);       // Функция поиска дрона в списке по цвету (так как у каждого дрона цвет уникальный)
void addDrone(drone_t *drone, node **head, freeColor_t **freeColor, int count); // Функция добавления автоматического дрона в список
void isCrash(node **droneList, freeColor_t **freeColor);  // Функция проверки столкновения дронов
void initDrone(drone_t **drone, int x, int y, int tsize, int droneCount);  // Инициализация дрона
int droneListCount(node *list);   // Функция подсчета дронов в списке
drone_t *checkDronePos(node *list, int x, int y);  // Функция проверяет наличие дрона по координатам
drone_t *checkDroneBasketPos(node *list, int x, int y);     // Функция проверяет наличие корзины дрона по координатам
int wayIsBusy(node *droneList, int x, int y);               // Функция проверяет наличие препятствий на пути у дрона
drone_t *moveDrone(drone_t *drone, int key);                // Функция движения дрона с ручным управлением
void putInBasket(drone_t **drone, pumpkins_t **pumpkins);   // Функция заполняет корзину
int putOutBasket(drone_t **drone);                          // Функция разгружает корзину
void selectTarget(drone_t **drone, pumpkins_t *pumpkins);   // Функция выбора цели для автоматического дрона
drone_t *autopilot(drone_t **drone, node *droneList);       // Функция движения дрона с автоматическим управлением

#endif