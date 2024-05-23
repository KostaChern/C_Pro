// Задание 1. Сколько раз встречается максимум
// На стандартном потоке ввода задается натуральное число N (N > 0), после
// которого следует последовательность из N целых чисел.
// На стандартный поток вывода напечатайте, сколько раз в этой
// последовательности встречается максимум.
// Указание: использовать массивы запрещается.
// Данные на входе: Натуральное число N (N > 0), после которого следует
// последовательность из N целых чисел.
// Данные на выходе: Одно целое число.
// Пример №1
// Данные на входе: 6 1 2 3 2 0 3
// Данные на выходе: 2
// Пример №2
// Данные на входе: 3 5 2 -1
// Данные на выходе: 1


#include <stdio.h>
#include <stdint.h>

int main()
{
	uint32_t N;
	printf("Enter a number N (N > 0), then push Enter\n");
	scanf("%d", &N);
	printf("Enter the numbers one at a time\n");
	uint32_t count = 0;
	uint32_t max = 0;
	uint32_t temp = 0;
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &temp);
		if (temp > max)
		{
			max = temp;
			count = 1;
		}
		else if (temp == max)
		{
			count++;
		}
	}
	
	printf("MAXimum number printed => %u times\n", count);
	return 0;
}

