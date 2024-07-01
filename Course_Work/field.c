#include "field.h"

void initField(char matrix[MAX_X][MAX_Y])
{
    /*
    Отрисовка границ поля
    */
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            if (i == 0 || i == MAX_X - 5 || i == MAX_X - 1)
            {
                matrix[i][j] = '-';
            }
            else if (j == 0 || j == MAX_Y - 1)
            {
                matrix[i][j] = '|';
            }
            else
            {
                matrix[i][j] = ' ';
            }
        }
    }
}

void printField(char matrix[MAX_X][MAX_Y], pumpkins_t *list, node *droneList, drone_t *drone1)
{
    /*
    Функция проверяет по координатам матрицы наличие и состояние объекта. 
    Если они подходят по условиям, то выводится конкретное значение и цвет.
    */
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int state = 0;
    node *droneListPtr = droneList;
    drone_t *droneForPrint = NULL;
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {   
            if (drone1->x == i && drone1->y == j)
            {
                SetConsoleTextAttribute(hStdOut, BLUE);
                printf("X");
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            
            else if(drone1->basket->x == i && drone1->basket->y == j && drone1->basket->isEmpty == 1)
            {
                SetConsoleTextAttribute(hStdOut, BLUE);
                printf("O");
                SetConsoleTextAttribute(hStdOut, RESETDEV);
            }
            else if ((droneForPrint = checkDronePos(droneListPtr, i, j)) != NULL)
                {
                    SetConsoleTextAttribute(hStdOut, droneForPrint->color);
                    printf("X");
                    SetConsoleTextAttribute(hStdOut, RESETDEV);
                }
            else if ((droneForPrint = checkDroneBasketPos(droneListPtr, i, j)) != NULL)
                {
                    SetConsoleTextAttribute(hStdOut, droneForPrint->color);
                    printf("O");
                    SetConsoleTextAttribute(hStdOut, RESETDEV);
                }
            else if (state = findPumpkinState(list, i, j))
            {
                if (state == 1)
                {
                    SetConsoleTextAttribute(hStdOut, GREEN);
                    printf("o");
                    SetConsoleTextAttribute(hStdOut, RESETDEV);
                }
                else if (state == 2)
                {
                    SetConsoleTextAttribute(hStdOut, YELLOW);
                    printf("O");
                    SetConsoleTextAttribute(hStdOut, RESETDEV);
                }
                else if (state == 3)
                {
                    printf(" ");
                }
            }
            else
            {
                printf("%c", matrix[i][j]);
            }
        }
        printf("\n");
    }
}