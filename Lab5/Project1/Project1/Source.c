#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <locale.h>


typedef struct stack_t
{
	int value;
	struct stack_t* next;
} TStack;

void PushS(TStack** stack, int value)
{
	TStack* node = (TStack*)malloc(sizeof(TStack));
	node->value = value;
	node->next = *stack;
	*stack = node;
}

void Delete(TStack** stack)
{
	TStack* node= *stack;
	if (node != NULL)
	{
		*stack = (*stack)->next;
		free(node);
	}
}

void PrintS(TStack* stack)
{
	TStack* node = stack;
	while(node!=NULL)
	{
		printf("%d ",node->value);
		node = node->next;
	}
	printf("\n");
}

void ClearS(TStack** stack)
{
	TStack* node;
	while (*stack != NULL)
	{
		node = *stack;
		*stack = (*stack)->next;
		free(node);
	}
}

//-----------------------------------------------------------------------------

typedef struct node_t
{
	int num;
	char mode;
	int value;
	struct node_t* next;
}  TNode;

typedef struct queue_t
{
	TNode* head;
	TNode* tail;
}  TQueue;

void PushQ(TQueue* queue, int num, char mode, int value)
{
	TNode* node = malloc(sizeof(TNode));
	node->num = num;
	node->mode = mode;
	node->value = value;
	node->next = NULL;
	if (queue->head && queue->tail)
	{
		queue->tail->next = node;
		queue->tail = node;
	}
	else
	{
		queue->head = queue->tail = node;
	}
}

void Change(TQueue* queue, TStack** stacks, int N)
{
	TNode* node = queue->head;
	while (node)
	{
		switch (node->mode)
		{
			case 'A':
			{
				PushS(&stacks[(node->num)-1], node->value);
			}
			break;
			case 'D':
			{
				Delete(&stacks[(node->num)-1]);
			}
			break;
			default:; break;
		}
		node = node->next;
	}
	for (int i = 0; i < N; i++)
	{
		PrintS(stacks[i]);
	}
}

void ClearQ(TQueue* queue)
{
	TNode *node = queue->head;
	while (queue->head)
	{
		node = queue->head;
		queue->head = queue->head->next;
		free(node);
	}
	queue->head = queue->tail = NULL;
}

void PrintQ(const TQueue* queue)
{
	TNode* node = queue->head;
	while (node)
	{
		printf("%d;%c;%d ", node->num, node->mode, node->value);
		node = node->next;
	}
	printf("\n");
}


int main()
{
	setlocale(LC_CTYPE, "Russian");
	int N, n, num, val;
	char mod=' ';
	printf("Количесво стеков=");
	scanf_s("%d", &N);
	printf("Количесво элнментов очереди=");
	scanf_s("%d", &n);
	printf("\n");
	TStack **stacks = (TStack**)malloc(N * sizeof(TStack*));
	for (int i = 0; i < N; i++)
	{
		stacks[i] = NULL;
	}
	TQueue q;
	q.head = NULL;
	q.tail = NULL;
	for (int i = 0; i < n; i++)
	{
		printf("Номер стека ");
		scanf_s("%d", &num);
		printf("Режим обработки ");
		scanf_s("\n%c", &mod);
		val = 0;
		if (mod == 'A')
		{
			printf("Значение ");
			scanf_s("%d", &val);
		}
		printf("\n");
		PushQ(&q, num, mod, val);
	}
	Change(&q, stacks, N);
	PrintQ(&q);
	for (int i = 0; i < N; i++)
	{
		ClearS(&stacks[i]);
	}
	free(stacks);
	_getch();
	return 0;
}