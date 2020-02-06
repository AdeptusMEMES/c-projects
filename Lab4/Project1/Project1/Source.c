#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <locale.h>

void ItoB(int n, char*s, int b)
{
	_Bool min;
	if (n < 0)
		min = 1;
	else
		min = 0;
	n = abs(n);
	int N = 0;
	int q;
	do
	{
		N++;
		q = n % b;
		n /= b;
		for (int i = N - 1; i > 0; i--)
		{
			s[i] = s[i - 1];
		}
		if (q < 10)
			s[0] = q + 48;
		else
			s[0] = q + 55;
	} while (n != 0);
	if (min)
	{
		N++;
		for (int i = N - 1; i > 0; i--)
		{
			s[i] = s[i - 1];
		}
		s[0] = '-';
	}
	s[N] = '\0';
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int n,b;
	char s[256];
	printf("¬ведите число: ");
	scanf_s("%d", &n);
	printf("¬ведите основание системы счислени€: ");
	scanf_s("%d", &b);
	ItoB(n, s, b);
	printf("\n%d (10)= %s (%d)\n", n, s, b);
	_getch();
	return 0;
}