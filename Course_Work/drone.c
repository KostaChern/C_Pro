#include "drone.h"

void initFreeColor(freeColor_t **head)
{
    /*
    Заполнение списка цветов и их состояний
    */
    freeColor_t *res = calloc(1, sizeof(freeColor_t));

    res->color = WHITE;
    res->state = 0;
    res->next = calloc(1, sizeof(freeColor_t));
    res->next->color = CYAN;
    res->next->state = 0;
    res->next->next = calloc(1, sizeof(freeColor_t));
    res->next->next->color = RED;
    res->next->next->state = 0;
    res->next->next->next = calloc(1, sizeof(freeColor_t));
    res->next->next->next->color = MAGENTA;
    res->next->next->next->state = 0;
    res->next->next->next->next = NULL;

    *head = res;
}

void printColor(freeColor_t *list)
{
    /*
    Вывод на экран списка цветов. Модифицирована для отображения наличия работающего автоматического дрона на поле
    */
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    while (list != NULL)
    {
        SetConsoleTextAttribute(hStdOut, list->color);
        printf("%s\n", (list->state == 1) ? "The drone is working" : "The drone is ready to work");
        SetConsoleTextAttribute(hStdOut, RESETDEV);

        list = list->next;
    }
    printf("\n");
}

void initDrone(drone_t **drone, int x, int y, int tsize, int droneCount)
{
    /*
    Инициализация нового дрона
    */
    drone_t *newDrone = calloc(1, sizeof(drone_t));
    newDrone->x = x;
    newDrone->y = y;
    newDrone->targetX = x;
    newDrone->targetY = y + droneCount;
    newDrone->defTargetX = x;
    newDrone->defTargetY = y + droneCount;
    newDrone->direction = UP;
    newDrone->color = WHITE;
    newDrone->atWork = 0;
    newDrone->tsize = tsize;
    newDrone->basket = (basket_t *)malloc(sizeof(basket_t));
    newDrone->basket->isEmpty = 0;

    if (*drone == NULL)
    {
        *drone = newDrone;
    }
    else
    {
        return;
    }
}

void isCrash(node **droneList, freeColor_t **freeColor)
{
    /*
    Проверка совпадения текущих координат дрона и координат дронов из списка. 
    Если координаты совпали, дрон в которого врезались, удаляется.
    */
    node *droneListPtr = *droneList;
    node *droneListPtrCurrent = *droneList;
    node *toRemove = NULL;
    freeColor_t *freePtr = *freeColor;
    while (droneListPtr != NULL)
    {
        while (droneListPtrCurrent != NULL)
        {
            if (droneListPtr->drone->defTargetY != droneListPtrCurrent->drone->defTargetY)
            {
                if (droneListPtr->drone->x == droneListPtrCurrent->drone->x && droneListPtr->drone->y == droneListPtrCurrent->drone->y)
                {
                    toRemove = findNode(droneListPtrCurrent, droneListPtrCurrent->drone->color);
                    while (freePtr != NULL)
                    {
                        if (freePtr->color == toRemove->drone->color)
                        {
                            freePtr->state = 0;
                            break;
                        }

                        freePtr = freePtr->next;
                    }

                    deleteNode(droneList, toRemove);
                }
                else if (droneListPtr->drone->x == droneListPtrCurrent->drone->basket->x && droneListPtr->drone->y == droneListPtrCurrent->drone->basket->y)
                {
                    toRemove = findNode(droneListPtrCurrent, droneListPtrCurrent->drone->color);
                    while (freePtr != NULL)
                    {
                        if (freePtr->color == toRemove->drone->color)
                        {
                            freePtr->state = 0;
                            break;
                        }

                        freePtr = freePtr->next;
                    }
                    deleteNode(droneList, toRemove);
                }
            }
            droneListPtrCurrent = droneListPtrCurrent->next;
        }
        droneListPtrCurrent = *droneList;

        droneListPtr = droneListPtr->next;
    }
}

void addDrone(drone_t *drone, node **head, freeColor_t **freeColor, int count)
{
    /*
    Добавление дрона в список
    */
    node *res = calloc(1, sizeof(node));
    node *nodePtr = *head;
    freeColor_t *freePtr = *freeColor;
    if (count > 3)
    {
        return;
    }
    else
    {
        res->drone = drone;
        res->number = count;
        while (freePtr != NULL)
        {
            if (freePtr->state == 0)
            {
                res->drone->color = freePtr->color;
                freePtr->state = 1;
                break;
            }

            freePtr = freePtr->next;
        }

        if (*head == NULL)
        {
            *head = res;
        }
        else
        {
            node *p = *head;
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = res;
        }
    }
}

int droneListCount(node *list)
{
    /*
    Функция подсчета дронов в списке
    */
    node *ptr = list;
    int count = 0;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }
    return count;
}

drone_t *checkDronePos(node *list, int x, int y)
{
    /*
    Функция проверяет наличие дрона по координатам
    */
    node *ptr = list;
    while (ptr != NULL)
    {
        if (ptr->drone->x == x && ptr->drone->y == y)
        {
            return ptr->drone;
        }
        ptr = ptr->next;
    }
    return NULL;
}


drone_t *checkDroneBasketPos(node *list, int x, int y)
{
    /*
    Функция проверяет наличие корзины дрона по координатам
    */
    node *ptr = list;
    while (ptr != NULL)
    {
        if (ptr->drone->basket->x == x && ptr->drone->basket->y == y && ptr->drone->basket->isEmpty == 1)
        {
            return ptr->drone;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void deleteNode(node **head, node *toRemove)
{
    /*
    Удаление дрона из списка
    */
    if ((*head) == toRemove)
    {
        *head = toRemove->next;
        free(toRemove);
        return;
    }
    node *ptr = *head;
    while (ptr != NULL && ptr->next != toRemove)
    {
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        return;
    }
    ptr->next = toRemove->next;
    free(toRemove);
}

node *findNode(node *head, char color)
{
    /*
    Вспомогательная функция для удаления дрона.
    */
    node *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->drone->color == color)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}


int wayIsBusy(node *droneList, int x, int y)
{
    /*
    Функция получает координаты следующего хода дрона, сравнивает их с координатами
    дронов из списка и возвращает 1 или 0 в зависимости от того свбоден путь или нет.
    */
    node *droneListPtr = droneList;
    while (droneListPtr != NULL)
    {
        if (droneListPtr->drone->x == x && droneListPtr->drone->y == y)
        {
            return 1;
        }
        else if (droneListPtr->drone->basket->x == x && droneListPtr->drone->basket->y == y)
        {
            return 1;
        }
        droneListPtr = droneListPtr->next;
    }
    return 0;
}

drone_t *moveDrone(drone_t *drone, int key)
{
    /*
    Передвижение дрона с ручным управлением
    */
    drone->basket[0].x = drone->x;
    drone->basket[0].y = drone->y;

    if (key == LEFT)
    {
        if (drone->y == 1)
        {
            drone->y = 1;
            drone->direction = STOP;
        }
        else
        {
            drone->y = drone->y - 1;
            drone->direction = LEFT;
        }
    }
    else if (key == UP)
    {
        if (drone->x == 1)
        {
            drone->x = 1;
            drone->direction = STOP;
        }
        else
        {
            drone->x = drone->x - 1;
            drone->direction = UP;
        }
    }
    else if (key == RIGHT)
    {
        if (drone->y == MAX_Y - 2)
        {
            drone->y = MAX_Y - 2;
            drone->direction = STOP;
        }
        else
        {
            drone->y = drone->y + 1;
            drone->direction = RIGHT;
        }
    }
    else if (key == DOWN)
    {
        if (drone->x == MAX_X - 2)
        {
            drone->x = MAX_X - 2;
            drone->direction = STOP;
        }
        else
        {
            drone->x = drone->x + 1;
            drone->direction = DOWN;
        }
    }
    else if (key == STOP)
    {
        drone->direction = STOP;
    }

    return drone;
}

drone_t *autopilot(drone_t **drone, node *droneList)
{
    /*
    Сначала функция выбирает направление дрона по установленным координатам.
    Далее проверяет препятствия на пут, если их нет то движение в нужном направлении, если есть, то попытка увернуться.
    */
    drone_t *currentDrone = *drone;
    int key = STOP;

    if (currentDrone->x == currentDrone->targetX && currentDrone->y == currentDrone->targetY && currentDrone->direction == STOP)
    {
        currentDrone->atWork = 0;
    }
    if (currentDrone->x != currentDrone->targetX)
    {
        key = (currentDrone->x > currentDrone->targetX) ? UP : DOWN;
    }
    else if (currentDrone->y != currentDrone->targetY)
    {
        key = (currentDrone->y > currentDrone->targetY) ? LEFT : RIGHT;
    }

    else if (currentDrone->x == currentDrone->targetX && currentDrone->y == currentDrone->targetY)
    {
        currentDrone->direction = STOP;
    }

    currentDrone->basket[0].x = currentDrone->x;
    currentDrone->basket[0].y = currentDrone->y;

    if (key == LEFT)
    {
        if (wayIsBusy(droneList, currentDrone->x, currentDrone->y - 1))
        {
            currentDrone->direction = UP;
            currentDrone->x = currentDrone->x - 1;
        }

        else
        {
        if (currentDrone->y == 1)
        {
            currentDrone->y = 1;
            currentDrone->direction = STOP;
        }
        else
        {
            currentDrone->y = currentDrone->y - 1;
            currentDrone->direction = LEFT;
        }
        }
    }
    else if (key == UP)
    {
        if (wayIsBusy(droneList, currentDrone->x - 1, currentDrone->y) == 1)
        {
            currentDrone->y = currentDrone->y - 1;
            currentDrone->direction = LEFT;
        }

        else
        {
        if (currentDrone->x == 1)
        {
            currentDrone->x = 1;
            currentDrone->direction = STOP;
        }
        else
        {
            currentDrone->x = currentDrone->x - 1;
            currentDrone->direction = UP;
        }
        }
    }
    else if (key == RIGHT)
    {
        if (wayIsBusy(droneList, currentDrone->x, currentDrone->y + 1) == 1)
        {
            currentDrone->direction = DOWN;
            currentDrone->x = currentDrone->x + 1;
        }
        else
        {
        if (currentDrone->y == MAX_Y - 2)
        {
            currentDrone->y = MAX_Y - 2;
            currentDrone->direction = STOP;
        }
        else
        {
            currentDrone->y = currentDrone->y + 1;
            currentDrone->direction = RIGHT;
        }
        }
    }
    else if (key == DOWN)
    {
        if (wayIsBusy(droneList, currentDrone->x + 1, currentDrone->y) == 1)
        {
            currentDrone->y = currentDrone->y + 1;
            currentDrone->direction = RIGHT;
        }

        else
        {
        if (currentDrone->x == MAX_X - 2)
        {
            currentDrone->x = MAX_X - 2;
            currentDrone->direction = STOP;
        }
        else
        {
            currentDrone->x = currentDrone->x + 1;
            currentDrone->direction = DOWN;
        }
        }
    }
    else if (key == STOP)
    {
        currentDrone->direction = STOP;
    }
}

void putInBasket(drone_t **drone, pumpkins_t **pumpkins)
{
    /*
    Функция сравнивает координаты дрона с координатами тыкв из списка, если такая тыква нашлась и она спелая, 
    то корзина дрона заполняется. Его цель становится зоной разгрузки. 
    А состояние тыквы - собрана.
    */
    drone_t *dronePtr = *drone;
    if (dronePtr->basket->isEmpty == 1)
    {
        return;
    }

    int posX = dronePtr->x;
    int posY = dronePtr->y;
    int state = 0;
    pumpkins_t *ptr = findPumpkinPos(*pumpkins, posX, posY);
    if (state = findPumpkinState(*pumpkins, posX, posY))
    {
        if (state == 2)
        {
            dronePtr->basket->isEmpty = 1;
            ptr->state = 3;
            dronePtr->targetX = dronePtr->defTargetX;
            dronePtr->targetY = dronePtr->defTargetY;
        }
    }
}

int putOutBasket(drone_t **drone)
{
    /*
    Когда дрон дбирается до зоны выгрузки, корзина становится пустой.
    Дрон переходит в режим ожидания новой цели.
    Из функции возвращается значение, которое добавляется к счетчику собранных тыкв.
    */
    drone_t *dronePtr = *drone;
    int posX = dronePtr->x;
    int posY = dronePtr->y;
    if (posX == 11 && (posY > 0 && posY < MAX_Y))
    {
        if (dronePtr->basket->isEmpty == 1)
        {
            dronePtr->basket->isEmpty = 0;
            dronePtr->atWork = 0;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

void selectTarget(drone_t **drone, pumpkins_t *pumpkins)
{
    /*
    Если корзина дрона пуста, то произходит поиск спелой тыквы.
    Если она нашлась, то ее координаты станоятся целью дрона.
    */
    drone_t *dronePtr = *drone;
    pumpkins_t *ptr = NULL;
    if (dronePtr->basket->isEmpty == 0)
    {
        ptr = getRipePumpkin(pumpkins);
        if (ptr != NULL)
        {
            dronePtr->targetX = ptr->x;
            dronePtr->targetY = ptr->y;
            dronePtr->atWork = 1;
        }
    }
    else
    {
        dronePtr->targetX = 11;
        dronePtr->targetY = 10;
        dronePtr->atWork = 1;
    }
}