#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int k, K, P, D = 1, d = 0, n;
	printf("k=");
	scanf_s("%d", &k);
	for (int i = 0; i < k;)
	{
		P = D;
		n = 0;
		while (P > 0)
		{
			P /= 10;
			n++;
		}
		P = D;
		for (int j = 1; j <= n && i < k; j++)
		{
			K = P /(int)pow(10, n - j);
			printf("%d", K);
			P = P % (int)pow(10, n - j);
			i++;
		}
		D += d;
		d = D-d;
	}
	printf("\n%d-я цифра равна %d", k, K);
	_getch();
	return 0;
}