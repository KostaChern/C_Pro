// Задание 3. Префикс и суффикс
// Реализовать программу 3-го практического задания более эффективным
// способом со сложностью О(n) (см. код в лекции).
// Пример №1
// Данные на вход:
// don't_panic
// nick_is_a_mastodon
// Данные на выход: 3
// Пример №2
// Данные на вход:
// monty_python
// python_has_list_comprehensions
// Данные на выход: 6


#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

enum
{
    maxlength = 10001
};
int search_prefix(char *, char *);

int main()
{
    system("cls");
    char s1[maxlength], s2[maxlength];
    puts("Enter string 1 :");
    scanf("%10001s", s1);
    puts("Enter string 2 :");
    scanf("%10001s", s2);
   
    printf("%d %d\n", search_prefix(s1, s2), search_prefix(s2, s1));
    return 0;
}

int search_prefix(char *s1, char *s2)
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int i1, i2, max = 0, count = 0;
    char c1, c2;
    for (i1 = 0, i2 = 0; i1 < l1; i2++)
    {
        c1 = s1[i1];
        c2 = s2[i2];
        if (c1 == c2)              
        {
            i1++;                  
            count += 1;            
        }
        if(c1 != c2 && count > 0)   
        {
            if (count > max)       
            {
                max = count;       
            }
            count = 0;             
            i1 = 0;                
            i2--;                  
        }
        if (count == l2)           
        {
            max = count;
        }
        if (i2 >= l2)              
        {
            break;
        }
    }
    return max;
}