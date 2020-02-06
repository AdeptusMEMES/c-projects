#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

void in(char **A,int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			*(*(A + i) + j) = 'o';
		}
	}
	*(*(A + N - 1)) = 'x';
}

void show(char **A, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%c", *(*(A + i) + j));
		}
		printf("\n");
	}
}

void eat(char **A, int N, int M)
{
	int str, col;
	do
	{
		printf("\nСтрока:");
		scanf_s("%d", &str);
		printf("Столбец:");
		scanf_s("%d", &col);
		if (str <= 0 || str > N || col <= 0 || col > M || *(*(A + str-1) + col-1)==' ')
			printf("\nНеверный ввод\n");
	}while (str <= 0 || str > N || col <= 0 || col > M || *(*(A + str-1) + col-1)==' ');
	for (int i = str-1; i>=0; i--)
	{
		for (int j = col-1; j < M; j++)
		{
			*(*(A + i) + j) = ' ';
		}
	}
	printf("\n");
}

_Bool win(char **A, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (*(*(A + i) + j) != ' ')
				return 1;
		}
	}
	return 0;
}

void heig(char **A, int *N, int M)
{
	_Bool b=1;
	for (int j = 0; j < M; j++)
	{
		if (*(*(A)+j) != ' ')
			b = 0;
	}
	while (b && (*N) > 1)
	{
		for (int i = 0; i < (*N)-1; i++)
		{
			for (int j = 0; j < M; j++)
			{
				*(*(A + i) + j) = *(*(A + i+1) + j);
			}
		}
		(*N)--;
		b = 1;
		for (int j = 0; j < M; j++)
		{
			if (*(*(A)+j) != ' ')
				b = 0;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int N, M;
	printf("Число строк:");
	scanf_s("%d", &N);
	printf("Число столбцов:");
	scanf_s("%d", &M);
	char **A = (char **)malloc(N* sizeof(char *));
	for (int i = 0; i < N; i++)
	{
		A[i] = (char *)malloc(M* sizeof(char));
	}
	in(A, N, M);
	show(A, N, M);
	do
	{
		eat(A, N, M);
		heig(A, &N, M);
		show(A, N, M);
	} while (win(A, N, M));
	printf("Вы проиграли!\n");
	for (int i = 0; i < N; i++)
	{
		free(A[i]);
	}
	free(A);
	_getch();
	return 0;
}