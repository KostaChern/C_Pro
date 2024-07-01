#include "pumpkins.h"

int getRand()
{
    return rand() % 73;
}

void insertPumpkin(pumpkins_t **head, int x, int y, int count)
{
    /*
    Функция добавляет новую тыкву в список
    */
    pumpkins_t *res = calloc(1, sizeof(pumpkins_t));
    res->x = x;
    res->y = y;
    res->number = count;
    res->state = 1;
    if (*head == NULL)
    {
        *head = res;
    }
    else
    {
        pumpkins_t *p = *head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = res;
    }
}

void initPumpkins(pumpkins_t **head)
{
    /*
    Заполнение списка с тыквами
    */
    int count = 1;
    for (int i = 1; i < MAX_X - 5; i++)
    {
        for (int j = 2; j < MAX_Y - 1; j += 2)
        {
            insertPumpkin(head, i, j, count);
            count++;
        }
    }
}

int findPumpkinState(pumpkins_t *head, int x, int y)
{
    /*
    Функция возвращает сотояние тыквы, которая была найдена по координатам
    */
    pumpkins_t *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->x == x && ptr->y == y)
        {
            return ptr->state;
        }
        ptr = ptr->next;
    }
    return 0;
}

pumpkins_t *findPumpkin(pumpkins_t *head, int number)
{
    /*
    Функция ищет тыкву в списке по номеру
    */
    pumpkins_t *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->number == number)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

pumpkins_t *findPumpkinPos(pumpkins_t *head, int x, int y)
{
    /*
    Функция ищет тыкву в списке по номеру по координатам
    */
    pumpkins_t *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->x == x && ptr->y == y)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void ripening(pumpkins_t **head)
{
    /*
    Функция меняет состояние тыквы в случайном порядке
    */
    srand(time(NULL));
    int ripe = 0;
    pumpkins_t *ptr;
    for (int i = 0; i < 72; i++)
    {
        ripe = getRand();
        ptr = findPumpkin(*head, ripe);
        if (ptr != NULL && ptr->state == 1)
        {
            ptr->state = 2;
            break;
        }
    }
}

pumpkins_t *getRipePumpkin(pumpkins_t *head)
{
    /*
    Функция возвращает случайную тыкву, которая созрела
    */
    pumpkins_t *ptr = head;
    int check = getRand();
    for (int i = 0; i < 50; i++)
    {
        while (ptr != NULL)
        {
            if (ptr->number == check)
            {
                if (ptr->state == 2)
                {
                    return ptr;
                }   
            }
            ptr = ptr->next;
        }
        check = getRand();
    }
    
    return NULL;
}