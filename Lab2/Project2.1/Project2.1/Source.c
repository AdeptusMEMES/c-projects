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
	printf("\nВведите баллы ЦТ по русскому языку\n");
	scanf_s("%d", &r);
	printf("\nВведите баллы ЦТ по математике\n");
	scanf_s("%d", &m);
	printf("\nВведите баллы ЦТ по физике\n");
	scanf_s("%d", &p);
	printf("\nВведите балл аттестата\n");
	scanf_s("%d", &c);
	_Bool hum = (r / m >= 2 && r / p >= 2);
	_Bool cor = (r >= 0 && r <= 100 && m >= 0 && m <= 100 && p >= 0 && p <= 100 && c>= 0 && c <= 100);
	int s = p + m + r + c;
	if (s < list[4].min && !hum && cor)
		printf("\nС вашими результатами не стоит тратить время на поступление в наш вуз.\n\n");
	if (s == list[4].min && !hum && cor)
		printf("\nФакультет КП\n\n");
	if (s < list[3].min && s > list[2].min && !hum&&cor)
		printf("\nФакультет РЭ\n\n");
	if (s < list[1].min && s >=list[3].min && !hum&&cor)
		printf("\nФакультет ИК\n\n");
	if (s < list[0].min&&s>= list[1].min && !hum&&cor)
		printf("\nФакультет ИТУ\n\n");
	if (s >= list[0].min && !hum&&cor)
		printf("\nФакультет КСиС\n\n");
	if (!cor && !hum)
		printf("\nНеверный ввод\n\n");
	if (cor && hum)
		printf("\nЗадумайтесь над поступлением в гуманитарный вуз.\n\n");
	if (!cor)
		printf("\nНеверный ввод\n\n");
}

void in(struct faq *list)
{
	list[0].inf = "КСиС";
	list[0].min = 277;
	list[1].inf = "ИТУ";
	list[1].min = 166;
	list[2].inf ="РЭ";
	list[2].min = 119;
	list[3].inf = "ИК";
	list[3].min = 127;
	list[4].inf = "КП";
	list[4].min = 118;
}

void red(struct faq *list)
{
	printf("\nРед.факультет:\n");
	printf("1.КСиС.\n2.ИТУ.\n3.РЭ.\n4.ИК.\n5.КП.\n");
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
		printf("1.Вывод информации о факультете КСиС.\n2.Вывод информации о факультете ИТУ.\n3.Вывод информации о факультете РЭ.");
		printf("\n4.Вывод информации о факультете ИК.\n5.Вывод информации о факультете КП.\n6.Рекомендации.\n7.Редактировать\n8.Выход\n");
		scanf_s("%d", &k);
		if (k >= 1 && k <= 5)
			printf("%s Проходной балл:%d\n", list[k - 1].inf, list[k - 1].min);
		if (k == 6)
			rec(list);
		if (k == 7)
			red(list);
	} while (k != 8);
	_getch();
	return 0;
}