#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <Windows.h>
#include "drone.h"
#include "pumpkins.h"
#include "field.h"

#define MAX_X 14 // row
#define MAX_Y 21 // col
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4
#define STOP 5

int checkDirection(drone_t *drone, int key); // Функция проверки направления дрона
int keyProcessing(drone_t *drone, int key, node **droneList, int droneCount, freeColor_t **freeColor, int result); // Функция обработки нажатия клавиш
void userPause();  // Функция отрисовки паузы игры
int droneProcessing(node **droneList, pumpkins_t **listHarvest, freeColor_t **freeColor); // Функция обработки движения автоматических дронов
void checkEnd(pumpkins_t *listHarvest, int result);  // Функция проверки окончания игры
void startGame();  // Функция отрисовки стартового меню игры

int main()
{
    int harvestCounter = 0;   // Счетчик собранного урожая
    node *droneList = NULL;   // Список для автоматических дронов
    freeColor_t *freeColor = NULL;  // Список для определение не занятых цветов для создания дронов
    initFreeColor(&freeColor);      // Заполнение списка цветов
    int droneCount = droneListCount(droneList); // Подсчет количества автоматических дронов
    pumpkins_t *harvest = NULL; // Список тыкв
    drone_t *drone1 = NULL;     // Дрон с ручным управлением
    initDrone(&drone1, 11, 4, 0, droneCount);   // Инициализация дрона с ручным управлением
    initPumpkins(&harvest);                     // Заполнение списка с тыквами
    char matrix[MAX_X][MAX_Y];                  // Матрица игрового поля
    initField(matrix);                          // Отрисовка границ матрицы
    startGame();                                // Старт игры с подсказками по управлению
    printField(matrix, harvest, droneList, drone1);  // Отрисовка игрового поля
    int key = UP;                               // Переменная для обработки нажатия клавиш
    while (1)
    {
        system("cls");
        droneCount = droneListCount(droneList);     // Подсчет автоматических дронов, для ограничения до 5 штук на поле
        if (kbhit())                                // Проверка нажатой клавиши
        {
            key = keyProcessing(drone1, key, &droneList, droneCount, &freeColor, harvestCounter); // Передача направления дрону с ручным направлением
        }
        drone1 = moveDrone(drone1, key);            // Движение дрона с ручным направлением

        harvestCounter += droneProcessing(&droneList, &harvest, &freeColor); // Движение автоматических дронов, если дроны принесли урожай в зону выгрузки, то прибавляем к счетчику
        isCrash(&droneList, &freeColor); // проверка на столкновения
        putInBasket(&drone1, &harvest);  // Сбор урожая дроном с ручным направлением
        if (putOutBasket(&drone1))       // Выгрузка дрона с ручным направлением
        {
            harvestCounter++;
        }

        ripening(&harvest);     // Созревание урожая

        system("cls");      // Отрисовка игрового поля и текущего состояния
        printField(matrix, harvest, droneList, drone1);             
        printf("Has been harvested : %d \n", harvestCounter);
        printf("Control : <w> <a> <s> <d>\n");
        printf("Add a drone : <r>\n");
        printf("Pause : <p>    Exit : <q>\n");
        printColor(freeColor);
        checkEnd(harvest, harvestCounter); // Проветка окончания игры
        Sleep(300);
    }
    return 0;
}

void startGame()
{
    /*
    Функция отрисовывает подсказки по управлению в игре
    */
    system("cls");
    printf("\n");
    printf("\n");
    printf("    The harvest game\n");
    printf("\n");
    printf("\n");
    printf("Control : <w> <a> <s> <d>\n");
    printf("Add a drone : <r>\n");
    printf("Pause : <p>    Exit : <q>\n");
    printf("Press <Enter> to start\n");
    getchar();
}

void checkEnd(pumpkins_t *listHarvest, int result)
{
    /*
    Если все тыквы перешли в состояние "собрано (3), то игра окончена."
    */
    int endCount = 0;
    while (listHarvest != NULL)
    {
        if (listHarvest->state == 3)
        {
            endCount++;
        }
        listHarvest = listHarvest->next;
    }
    if (endCount == 72)
    {
        system("cls");
        printf("\n");
        printf("\n");
        printf("       END GAME\n");
        printf("Has been harvested : %d \n", result);
        printf("\n");
        printf("\n");
        sleep(5);
        exit(0);
    }
}

int droneProcessing(node **droneList, pumpkins_t **listHarvest, freeColor_t **freeColor)
{
    /*
    Функция проходит по списку автоматических дронов, которые находятся на поле и для каждого назначает цель,
    вызывает вспомогательную функция движения, а так же проверяет может ли дрон собрать или выгрузить тыкву.
    */
    node *listPtr = *droneList;
    pumpkins_t *harvestPtr = *listHarvest;
    freeColor_t *freePtr = *freeColor;
    int harvestCounter = 0;
    while (listPtr != NULL)
    {
        if (listPtr->drone->atWork == 0)
        {
            selectTarget(&listPtr->drone, harvestPtr);
        }
        autopilot(&listPtr->drone, listPtr);
        putInBasket(&listPtr->drone, &harvestPtr);
        if (putOutBasket(&listPtr->drone))
        {
            harvestCounter++;
        }
        listPtr = listPtr->next;
    }
    return harvestCounter;
}

int keyProcessing(drone_t *drone, int key, node **droneList, int droneCount, freeColor_t **freeColor, int result)
{
    /*
    Функция считывает из буфера нажатую клавишу. 
    И в соответствии с нажатой клавишей возмодны действия :
    - Указание направления дрону
    - Пауза игры
    - Окончание игры
    - Добавление автоматического дрона, если это возможно.
    */
    char ch = getch();
    fflush(stdin);
    if (ch == 'w' || ch == 'W')
    {
        if (checkDirection(drone, UP))
        {
            return UP;
        }
        else
            return STOP;
    }
    if (ch == 's' || ch == 'S')
    {
        if (checkDirection(drone, DOWN))
        {
            return DOWN;
        }
        else
            return STOP;
    }
    if (ch == 'a' || ch == 'A')
    {
        if (checkDirection(drone, LEFT))
        {
            return LEFT;
        }
        else
            return STOP;
    }
    if (ch == 'd' || ch == 'D')
    {
        if (checkDirection(drone, RIGHT))
        {
            return RIGHT;
        }
        else
            return STOP;
    }
    if (ch == 'p' || ch == 'P')
    {
        userPause();
        return drone->direction;
    }
    if (ch == 'r' || ch == 'R')
    {
        drone_t *droneNew = NULL;
        initDrone(&droneNew, 11, 4 + droneCount + droneCount, 0, droneCount);
        addDrone(droneNew, droneList, freeColor, droneCount);
        return drone->direction;
    }
    if (ch == 'q' || ch == 'Q')
    {
        system("cls");
        for (int i = 0; i < MAX_X; ++i)
        {
            if (i == 7)
            {
                printf("        END GAME         \n");
                printf("_________Result__________\n");
                printf(" Has been harvested : %d \n", result);
            }
            printf(" \n");
        }
        free(drone);
        free(drone->basket);
        sleep(4);
        exit(0);
    }
}

int checkDirection(drone_t *drone, int key)
{
    /*
    Функция не дает дрону развернуться на 180 градусов    
    */
    if (key == LEFT)
    {
        if (drone->direction == RIGHT)
        {
            return 0;
        }
    }
    if (key == UP)
    {
        if (drone->direction == DOWN)
        {
            return 0;
        }
    }
    if (key == RIGHT)
    {
        if (drone->direction == LEFT)
        {
            return 0;
        }
    }
    if (key == DOWN)
    {
        if (drone->direction == UP)
        {
            return 0;
        }
    }
    return 1;
}

void userPause()
{
    /*
    Функция ставит игру на паузу, до нажатия клавиши <p>
    */
    system("cls");
    for (int i = 0; i < MAX_X - 1; ++i)
    {
        if (i == 7)
        {
            printf("             PAUSE          \n");
        }
        printf("               \n");
    }

    printf("To return to the game, press <p>\n");
    char pch;
    while (1)
    {
        if ((pch = getch()) == 'p')
        {
            break;
        }
    }
}