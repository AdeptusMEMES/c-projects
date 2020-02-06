#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#define M_PI 3.141592653589

clock_t start, finish;

void ent(double *e)
{
	do
	{
		printf("\ne(>=0.0000001)=");
		scanf_s("%lf", &(*e));
		if ((*e) <0.0000001)printf("Неверный ввод");
	} while ((*e) <0.0000001);
}

double M(double x)
{
	while (x > 2 * M_PI)x -= 2 * M_PI;
	if (x > M_PI)x = -(x - M_PI);
	return x;
}

void sinrec(double *x, double *e, int *n, double *s,double *k)
{
	if (*n == 1)*k = *x;
	*s += *k;
	if (fabs(*s - sin(*x)) < *e)
	{
		*n = *n / 2 + 1;
		return 0;
	}
	else
	{
		*k = (-1)*(*k)*powf((*x), 2) / (powf((double)(*n), 2) + 3 * (double)(*n) + 2);
		*n += 2;
		sinrec(&(*x), &(*e), &(*n), &(*s), &(*k));
	}

}

void siniter(double *x, double *e, int *n, double *s, double *k)
{
	*n =-1;
	*s = 0;
	do
	{
		*k = (-1)*(*k)*powf((*x), 2) / (powf((double)(*n), 2) + 3 * (double)(*n) + 2);
		*n += 2;
		if (*n == 1)*k = *x;
		*s += *k;
	} while (fabs(*s - sin(*x)) > *e);
	*n = *n / 2 + 1;
	return 0;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int n=1;
	double e, x, s = 0, k = 0;
	printf("x=");
	scanf_s("%lf", &x);
	printf("sin(%lf) = %1f", x, sin(x));
	x = M(x);
	ent(&e);
	start = clock();
	for (int i = 0; i < 100000; i++)
	{
		n = 1;s = 0; k = 0;
		sinrec(&x, &e, &n, &s, &k);
	}
	finish = clock();
	printf("\nВремя выполненения рекурсивной функции:%.3lf*10^(-9) с; ",((double)(finish - start) / CLOCKS_PER_SEC)*1000);
	printf("\nРезультат рекурсивной функции:%lf; ", s);
	printf("n = %d", n);
	start = clock();
	start = clock();
	for (int i = 0; i < 100000; i++)
	{
		siniter(&x, &e, &n, &s, &k);
	}
	finish = clock();
	printf("\nВремя выполненения итерационной функции:%.3lf*10^(-9) с; ", ((double)(finish - start) / CLOCKS_PER_SEC)*1000);
	printf("\nРезультат итерационной функции:%lf; ", s);
	printf("n = %d\n", n);
	_getch();
	return 0;
}