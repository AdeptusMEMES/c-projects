#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

typedef struct NodeT
{
	int data;
	struct NodeT *left;
	struct NodeT *right;
	struct NodeT *parent;
} NodeT;

NodeT* NewNodeT(int value, NodeT *parent)
{
	NodeT* temp = (NodeT*)malloc(sizeof(NodeT));
	temp->left = temp->right = NULL;
	temp->data = value;
	temp->parent = parent;
	return temp;
}

NodeT* AddNodeT(NodeT *root, int value)
{
	if (root == NULL)
	{
		root = NewNodeT(value, NULL);
		return root;
	}
	NodeT *temp = root;
	NodeT *temp0 = root;
	while (temp != NULL)
	{
		temp0 = temp;
		if (value > temp->data)
			temp = temp->right;
		else
		{
			if (value < temp->data)
				temp = temp->left;
			else
			{
				if (value == temp->data)
					return root;
			}
		}
	}
	temp = NewNodeT(value, temp0);
	if (temp->data > temp->parent->data)
		temp->parent->right = temp;
	else
		temp->parent->left = temp;
	return root;
}

void FindMaxT(NodeT *root)
{
	NodeT *temp = root;
	if (temp == NULL)return 0;
	while (temp->right != NULL)
	{
		temp = temp->right;
	}
	printf("%d", temp->data);
}

void ClearT(NodeT **root)
{
	if (*root) 
	{
		if ((*root)->left)
		{
			ClearT(&((*root)->left));
		}
		if ((*root)->right)
		{
			ClearT(&((*root)->right));
		}
	}
	free(*root);
}

//-----------------------------------------------------------------------------

typedef struct NodeS
{
	NodeT *root;
	struct NodeS* next;
} NodeS;

NodeS* AddNodeS(NodeS* stack)
{
	NodeS* node = (NodeS*)malloc(sizeof(NodeS));
	node->root = NULL;
	node->next = stack;
	stack = node;
	return stack;
}

void ClearS(NodeS** stack)
{
	NodeS* node;
	while (*stack != NULL)
	{
		node = *stack;
		*stack = (*stack)->next;
		ClearT(&(node->root));
		free(node);
	}
}

//-----------------------------------------------------------------------------

typedef struct NodeL
{
	int data;
	int num;
	struct NodeL* next;
	struct NodeL* prev;
} NodeL;

void AddNodeL(NodeL** head, NodeL** tail, int data, int num)
{
	
	NodeL *node = (NodeL*)malloc(sizeof(NodeL));
	node->data = data;
	node->num = num;
	node->next = NULL;
	if (*head!= NULL)
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

void ShowList(NodeL* head)
{
	NodeL *node = head;
	while (node != NULL)
	{
		printf("Дерево:%d Число:%d\n", node->num, node->data);
		node = node->next;
	}
}

void ClearL(NodeL** head, NodeL **tail)
{
	while (*head != NULL)
	{
		*tail = (*head)->next;
		free(*head);
		*head = *tail;
	}
}


//-----------------------------------------------------------------------------

NodeS* AddNumsToStack(NodeS* stack, int data, int num)
{
	NodeS *node = stack;
	for (int i = 1; i < num; i++)
	{
		node = node->next;
	}
	node->root = AddNodeT(node->root, data);
	return stack;
}

void TakeNumsFromList(NodeL *head, NodeS **stack)
{
	NodeL *node = head;
	while (node != NULL)
	{
		*stack = AddNumsToStack((*stack), node->data, node->num);
		node = node->next;
	}
}

void ShowMax(NodeS* stack)
{
	NodeS *node = stack;
	int i = 1;
	while (node != NULL)
	{
		printf("%d- ", i);
		FindMaxT(node->root);
		printf("\n");
		node = node->next;
		i++;
	}
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	NodeS *stack = NULL;
	NodeL *head = NULL;
	NodeL *tail = NULL;
	int N;
	printf("Количество деревьев:\n");
	scanf_s("%d", &N);
	for (int i = 0; i < N; i++)
	{
		stack= AddNodeS(stack);
	}
	int i, d, t=1;
	do
	{
		if (t == 1)
		{
			printf("\nЧисло:\n");
			scanf_s("%d", &d);
			printf("Номер дерева:\n");
			scanf_s("%d", &i);
			printf("\n");
			AddNodeL(&head, &tail, d, i);
		}
		printf("Продолжить ввод?\n1.Да  0.Нет\n");
		scanf_s("%d", &t);
	} while (t != 0);
	TakeNumsFromList(head, &stack);
	printf("\n");
	ShowList(head);
	printf("\n");
	ShowMax(stack);
	ClearL(&head, &tail);
	ClearS(&stack);
	free(stack);
	free(head);
	free(tail);
	_getch();
	return 0;
}