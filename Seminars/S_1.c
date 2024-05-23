// Циклический сдвиг
// Задача 1
// На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). 
// Требуется циклически сдвинуть биты числа N вправо на K битов и вывести полученное таким образом 
// число.
// Данные на входе: Два целых числа: 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31).
// Данные на выходе: Одно целое число

/*N 001011
K 2
110010*/

#include <stdio.h>
#include <stdint.h>

// int main(){
// uint32_t N;
// int K;
// scanf("%d %d", &N, &K);

// uint32_t res;
// uint32_t temp;

// uint32_t mask = ~0;
// mask >>= (32 - K); // 000011
// temp = N | mask;   // 000011
// temp <<= (32 - K); // 110000

// res = N >> K;
// res = res | temp;

// printf("%u\n", res);

// return 0;
// }

// uint32_t worker(uint32_t , unsigned int);
// int main (){
// unsigned int k;
// uint32_t n, res;
//  scanf("%u %u", &n, &k);
//  res = worker (n, k);
//  printf("%u\n", res);
//  return 0;
// }
// uint32_t worker (uint32_t n, unsigned int k)
// {
//  return n>>k | n<<(32-k);
// }

// Извлечение бит
// Задача 1
// На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). 
// Требуется взять K младших битов числа N и вывести полученное таким образом число.
// Данные на входе: Два целых числа: 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). 
// Данные на выходе: Одно целое число 
// Пример №1
// Данные на входе: 2 1
// Данные на выходе: 0
// Пример №2
// Данные на входе: 12 3
// Данные на выходе: 4

// void print8(x)
// {
//     for(int i = sizeof(x)<<3; i; i--)
//         putchar('0'+((x>>(i-1))&1));
// }

// int main(){
//     uint32_t N;
//     int K;
//     scanf("%u %d", &N, &K);
//     print8(N);
//     printf("\n");
//     // print8(K);
//     // printf("\n");

//     // uint32_t mask = (1 << K) - 1;
//     uint32_t res = N << (32 - K) >> (32 - K);

//     printf("%u\n", res);
//     print8(res);
//     printf("\n");
//     return 0;

// }

// Поиск последовательности бит
// Задача 2
// На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). 
// Требуется взять K подряд идущих битов числа N так, чтобы полученное число было максимальным. 
// Программа должна вывести полученное число.
// Данные на входе: Два целых числа: 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). 
// Данные на выходе: Одно целое число 
// Пример №1
// Данные на входе: 2 1
// Примечание: 2 = 0000 00102
// , максимальное число 1
// Данные на выходе: 1
// Пример №2
// Данные на входе: 12 3
// Примечание: 12 = 0000 11002
// , максимальное число 1102
//  = 6
// Данные на выходе: 6

// #include <stdio.h>
// #include <stdint.h>
// int main(){
// uint32_t N;
// int K;
// scanf("%d %d", &N, &K);

// // 000101000 - N K = 4
// // 0001 01000
// // 0 0010 1000
// // 00 0101 000
// // 000 1010 00
// uint32_t mask = ~0;
// mask <<= (32 - K);
// // 111100000

// uint32_t max = 0;
// // K = 31 2 варианта
// for (int i = 0; i <= (32 - K); ++i){
// uint32_t v = mask & N >> (32 - K - i);
// if (v > max){
// max = v;
// }
// mask >>= 1;
// }

// printf("%u", max);

// return 0;
// }

// РЕШЕНИЕ ИЗ МЕТОДИЧКИ:

// uint32_t worker(uint32_t ,int );
// uint32_t slice_bits(uint32_t, int start, int length);
// int main (){
// int k;
// uint32_t n, res;
//     scanf("%u %d", &n, &k);
//     res = worker (n, k);
//     printf("%u\n", res);
//     return 0;
// }
// uint32_t worker (uint32_t n, int k){
// uint32_t max = 0;// minimal value for unsigned types
//     for (int i = 0; i<=32-k ; i++)
//     {
//        uint32_t cur = slice_bits (n, i, k);
//        if(cur > max)
//        {
//            max = cur;
//        }
//     }
//     return max;
// }

// uint32_t slice_bits(uint32_t n, int start, int length)
// {
//     return(n & (~(uint32_t)0 >> (32-length))<<start ) >> start;
// }

// Подсчет битов
// Задача 2
// На вход программе подается беззнаковое 32-битное целое число N. Требуется найти количество 
// единичных битов в двоичном представлении данного числа.
// Данные на входе: 32-битное целое число N
// Данные на выходе: Одно целое число 
// Пример №1
// Данные на входе: 15
// Примечание: 15 = 0000 11112
// , сумма единиц равна 4
// Данные на выходе: 4
// Пример №2
// Данные на входе: 16
// Примечание: 16 = 0001 00002
// , сумма единиц равна 1
// Данные на выходе: 1

#include <stdio.h>
#include <stdint.h>
int main(){
uint32_t N;
scanf("%d", &N);

uint32_t mask = 1;

uint32_t count = 0;

for (int i = 0; i < 32; ++i)
{
uint32_t v = mask & N;
count+=v;
N >>= 1;
}
printf("%u\n", count);

return 0;
}