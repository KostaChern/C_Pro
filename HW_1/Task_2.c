// Задание 2. Инверсия старших
// На вход программе подается беззнаковое 32-битное целое число N. Требуется
// изменить значения всех битов старшего байта числа на противоположные и
// вывести полученное таким образом число.
// Данные на входе: Беззнаковое 32-битное целое число N
// Данные на выходе: Одно целое число.
// Пример №1
// Данные на входе: 1
// Данные на выходе: 4278190081
// Пример №2
// Данные на входе: 4278190081
// Данные на выходе: 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

 
int invert (const int num, const int bit) {
    const int mask = 1 << bit;
    return (num & mask)? (num & ~mask) : (num | mask);
}
 
void PrintBin (int n) {
    printf("\n");
    for (int i=31; i>=0; --i) {
        printf("%d", (n & (1 << i))? 1 : 0);
        if (i%4 == 0) printf(" ");
    }
}
 
int main (void) {
    uint32_t n, b;
    printf("n = ");
    scanf("%u", &n); 
    PrintBin(n); 
    for (size_t i = 24; i < 32; i++)
    {
        n = invert(n, i);
    }
    PrintBin(n);
    printf("\n%u\n",n); 
 
    return 0;
}