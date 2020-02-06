#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

struct faq
{
	int min;
	char *inf;
};

void rec(struct faq *list)
{
	int r, m, p, c;
	printf("\n������� ����� �� �� �������� �����\n");
	scanf_s("%d", &r);
	printf("\n������� ����� �� �� ����������\n");
	scanf_s("%d", &m);
	printf("\n������� ����� �� �� ������\n");
	scanf_s("%d", &p);
	printf("\n������� ���� ���������\n");
	scanf_s("%d", &c);
	_Bool hum = (r / m >= 2 && r / p >= 2);
	_Bool cor = (r >= 0 && r <= 100 && m >= 0 && m <= 100 && p >= 0 && p <= 100 && c>= 0 && c <= 100);
	int s = p + m + r + c;
	if (s < list[4].min && !hum && cor)
		printf("\n� ������ ������������ �� ����� ������� ����� �� ����������� � ��� ���.\n\n");
	if (s == list[4].min && !hum && cor)
		printf("\n��������� ��\n\n");
	if (s < list[3].min && s > list[2].min && !hum&&cor)
		printf("\n��������� ��\n\n");
	if (s < list[1].min && s >=list[3].min && !hum&&cor)
		printf("\n��������� ��\n\n");
	if (s < list[0].min&&s>= list[1].min && !hum&&cor)
		printf("\n��������� ���\n\n");
	if (s >= list[0].min && !hum&&cor)
		printf("\n��������� ����\n\n");
	if (!cor && !hum)
		printf("\n�������� ����\n\n");
	if (cor && hum)
		printf("\n����������� ��� ������������ � ������������ ���.\n\n");
	if (!cor)
		printf("\n�������� ����\n\n");
}

void in(struct faq *list)
{
	list[0].inf = "����";
	list[0].min = 277;
	list[1].inf = "���";
	list[1].min = 166;
	list[2].inf ="��";
	list[2].min = 119;
	list[3].inf = "��";
	list[3].min = 127;
	list[4].inf = "��";
	list[4].min = 118;
}

void red(struct faq *list)
{
	printf("\n���.���������:\n");
	printf("1.����.\n2.���.\n3.��.\n4.��.\n5.��.\n");
	int num,a;
	scanf_s("%d",&num);
	scanf_s("%d",&a);
	list[num - 1].min = a;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int k;
	struct faq *list = malloc(5);
	in(list);
	do
	{
		printf("1.����� ���������� � ���������� ����.\n2.����� ���������� � ���������� ���.\n3.����� ���������� � ���������� ��.");
		printf("\n4.����� ���������� � ���������� ��.\n5.����� ���������� � ���������� ��.\n6.������������.\n7.�������������\n8.�����\n");
		scanf_s("%d", &k);
		if (k >= 1 && k <= 5)
			printf("%s ��������� ����:%d\n", list[k - 1].inf, list[k - 1].min);
		if (k == 6)
			rec(list);
		if (k == 7)
			red(list);
	} while (k != 8);
	_getch();
	return 0;
}