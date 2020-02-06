#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void squeeze(char *s)
{
	for (int i = 0; s[i] != '\0'; i++)
	{
		if ((s[i] == ' '&&s[i + 1] == ' ') || (i == 0 && s[i] == ' ') || (s[i] == ' '&&s[i + 1] == '\0'))
		{
			int k;
			if (s[i] == ' '&&s[i + 1] == ' ')
				k = i + 1;
			if ((i == 0 && s[i] == ' ') || (s[i] == ' '&&s[i + 1] == '\0'))
				k = i;
			int n;
			for (n = 0; s[k] == ' '&&s[k] != '\0'; k++)
			{
				n++;
			}
			for (int j = k; s[j - 1] != '\0'; j++)
			{ 
				s[j - n] = s[j];
			}
		}
	}
}

void letterup(char **s, int N)
{
	_Bool u = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; s[i][j] != '\0'; j++)
		{
			if (s[i][j] == '.' || s[i][j] == '!' || s[i][j] == '?' || (i == 0 && j == 0))
				u = 1;
			if (u == 1)
			{
				if ((int)s[i][j] >= -64 && (int)s[i][j] <= -1)
					u = 0;
				if ((int)s[i][j] >= -32 && (int)s[i][j] <= -1)
					s[i][j] -= 32;
			}
			else
			{
				if ((int)s[i][j] >= -64 && (int)s[i][j] <= -33)
					s[i][j] += 32;
			}
		}
	}
}

int size(char pl[256])
{
	int N = 0;
	char e[256];
	FILE *file = fopen(pl,"r");
	while (fgets(e, 256, file) != NULL)N++;
	fclose(file);
	return N;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (fopen("E:\\C projects\\Lab4\\Project2\\Debug\\data.txt", "r") != NULL)
	{
		FILE *file = fopen("E:\\C projects\\Lab4\\Project2\\Debug\\data.txt", "r");
		int N = size("E:\\C projects\\Lab4\\Project2\\Debug\\data.txt");
		char **s = (char **)malloc(N * sizeof(char *));
		for (int i = 0; i < N; i++)
		{
			s[i] = (char *)malloc(256 * sizeof(char));
		}
		for (int i = 0; i < N; i++)
		{
			fgets(s[i], 256, file);
		}
		fclose(file);
		for (int i = 0; i < N; i++)
		{
			squeeze(s[i]);
		}
		letterup(s, N);
		file = fopen("E:\\C projects\\Lab4\\Project2\\Debug\\data.txt", "w");
		for (int i = 0; i < N; i++)
		{
			fputs(s[i], file);
		}
		fclose(file);
		for (int i = 0; i < N; i++)
		{
			free(s[i]);
		}
		free(s);
		printf("Файл откорректирован\n");
	}
	else printf("ОШИБКА! Файл не обнаружен\n");
	_getch();
	return 0;
}