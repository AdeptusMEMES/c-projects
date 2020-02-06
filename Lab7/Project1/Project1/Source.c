#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

typedef struct NodeL
{
	char **question;
	int n;
	char answer;
	struct NodeL* next;
	struct NodeL* prev;
} NodeL;

void AddNodeL(NodeL** head, NodeL** tail, char **question, int n, char answer)
{
	NodeL *node = (NodeL*)malloc(sizeof(NodeL));
	node->question= (char **)malloc(n * sizeof(char *));
	for (int i = 0; i < n; i++)
	{
		(node->question)[i] = (char *)malloc(256 * sizeof(char));
	}
	for (int i = 0; i < n; i++)
	{
		strcpy((node->question)[i], question[i]);
	}
	node->n = n;
	node->answer = answer;
	node->next = NULL;
	if (*head != NULL)
	{
		node->prev = *tail;
		(*tail)->next = node;
		*tail = node;
	}
	else
	{
		node->prev = NULL;
		*head = *tail = node;
	}
}

char** AddStr(char **S, int *n, char *s)
{
	(*n)++;
	char **s0 = (char **)malloc((*n) * sizeof(char *));
	for (int i = 0; i < (*n); i++)
	{
		s0[i] = (char *)malloc(256 * sizeof(char));
		if (i < (*n) - 1)
			strcpy(s0[i], S[i]);
	}
	strcpy(s0[(*n) - 1], s);
	return s0;
}

void LoadFromFileL(char *pl, NodeL **head, NodeL **tail)
{
	FILE *file = fopen(pl, "r");
	int n=0;
	char *s = (char *)malloc(256 * sizeof(char));
	char **s0 = (char **)malloc(sizeof(char *));;
	while (fgets(s, 256, file) != NULL)
	{
		if (strcmp(s, "//-----//\n") != 0)
			s0 = AddStr(s0, &n, s);
		else
		{
			fgets(s, 256, file);
			AddNodeL(&(*head), &(*tail), s0, n, s[0]);
			s0 = (char **)malloc(sizeof(char *));
			n = 0;
		}
	}
	fclose(file);
}

void RemoveNodeL(NodeL **head, NodeL **tail, NodeL *deleted)
{
	NodeL *node = *head;
	while (node != NULL&&node!= deleted)
	{
		node = node->next;
	}
	if (node != NULL)
	{
		if (node->prev != NULL)
			node->prev->next = node->next;
		if (node->next != NULL)
			node->next->prev = node->prev;
		if (node == *head)
			*head = (*head)->next;
		if(node== *tail)
			*tail = (*tail)->prev;
		free(node);
	}
}

void SaveToFileL(char *pl, NodeL *head)
{
	FILE *file = fopen(pl, "w");
	NodeL *node = head;
	while (node != NULL)
	{
		for (int i = 0; i < node->n; i++)
		{
			fputs((node->question)[i], file);
		}
		fputs("//-----//\n", file);
		fputc((node->answer), file);
		fputc('\n', file);
		node = node->next;
	}
	fclose(file);
}

void ClearL(NodeL **head, NodeL **tail)
{
	while (*head != NULL)
	{
		*tail = (*head)->next;
		free(*head);
		*head = *tail;
	}
}

//-----------------------------------------------------------------------------

void AddQuestion(NodeL** head, NodeL **tail)
{
	int k = 0;
	while (k != 2)
	{
		printf("\n\nЖелаете ввести вопрос?\n1.Да\n2.Нет\n");
		scanf_s("%d", &k);
		if (k == 1)
		{
			getchar();
			printf("\nВведите вопрос(введите '//-----//', чтобы закончить вводить)\n");
			int N = 0;
			char **S = (char **)malloc(N * sizeof(char *));
			char *s = (char *)malloc(256 * sizeof(char));
			char A;
			do
			{
				gets(s, 256);
				strcat(s, "\n");
				if (strcmp("//-----//\n", s) != 0)
					S = AddStr(S, &N, s);
			} while (strcmp("//-----//\n", s) != 0);
			printf("Введите правильный ответ\n");
			scanf_s("%c", &A);
			getchar();
			AddNodeL(&(*head), &(*tail), S, N, A);
		}
	}
}

void RemoveQuestion(NodeL** head, NodeL **tail)
{
	int k = 0;
	NodeL *node = *head;
	while (node != NULL && k != 4)
	{
		printf("\n\n");
		for (int i = 0; i < node->n; i++)
		{
			printf("%s", node->question[i]);
		}
		printf("Правильный ответ:%c\n\n", node->answer);
		printf("1.Следующий\n2.Предыдущий\n3.Удалить\n4.Выйти\n");
		scanf_s("%d", &k);
		switch (k)
		{
			case 1:
			{
				if (node->next != NULL)
					node = node->next;
			}break;
			case 2:
			{
				if (node->prev != NULL)
					node = node->prev;
			}break;
			case 3:
			{
				RemoveNodeL(&(*head), &(*tail), node);
				node = *head;
			}
			default:; break;
		}
	}
}

void Testing(NodeL *head)
{
	NodeL *node = head;
	char answer;
	int N = 0, N0 = 0;
	while (node != NULL)
	{
		N++;
		printf("\n\n");
		for (int i = 0; i < node->n; i++)
		{
			printf("%s", node->question[i]);
		}
		getchar();
		scanf_s("%c", &answer);
		if (answer == node->answer)
			N0++;
		node = node->next;
	}
	if (N > 0)
	{
		int result = (int)((double)N0 / (double)N * 100);
		printf("\n\nВерно выполнено %d %% задания",result);
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (fopen("E:\\C projects\\Lab7\\Project1\\data.txt", "r") != NULL)
	{
		NodeL *Head = NULL;
		NodeL *Tail = NULL;	
		int k = 0, k0 = 0;
		while (k != 3)
		{
			ClearL(&Head, &Tail);
			LoadFromFileL("E:\\C projects\\Lab7\\Project1\\data.txt", &Head, &Tail);
			printf("\n\n1.Изменить\n2.Пройти\n3.Выйти\n");
			scanf_s("%d", &k);
			switch (k)
			{
				case 1:
				{
					while (k0 != 3)
					{
						printf("\n\n1.Добавить\n2.Удалить\n3.Выйти\n");
						scanf_s("%d", &k0);
						switch (k0)
						{
							case 1:AddQuestion(&Head, &Tail); break;
							case 2:RemoveQuestion(&Head, &Tail); break;
							default:; break;
						}
					}
					SaveToFileL("E:\\C projects\\Lab7\\Project1\\data.txt", Head);
				}break;
				case 2:Testing(Head); break;
				default:; break;
			}
		}
		ClearL(&Head, &Tail);
	}
	else 
		printf("ОШИБКА! Файл не обнаружен\n");
	_getch();
	return 0;
}