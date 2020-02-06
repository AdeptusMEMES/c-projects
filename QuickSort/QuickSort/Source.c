#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void qs(int* m, int a, int *b)
{
	int k = *b;
	int l = a;
	int r = *b - 1;
	while (l <= r)
	{
		if (m[r] >= m[k] && m[l] < m[k])
		{
			int temp = m[l];
			m[l] = m[r];
			m[r] = temp;
		}
		if (m[r] < m[k])r--;
		if (m[l] >= m[k])l++;
	}
	int temp = m[l];
	m[l] = m[k];
	m[k] = temp;
	if (l < *b)qs(m, l + 1, &k);
	if (r > a)qs(m, a, &r);
}

int main()
{
	int n, k;
	scanf_s("%d", &n);
	int* M = (int*)malloc(sizeof(int));
	for (int i = 0; i < n; i++) 
	{ 
		scanf_s("%d", &k); 
		M[i] = k; 
	}
	k = n - 1;
	qs(M, 0, &k);
	for (int i = 0; i < n; i++)
	{
		k = M[i];
		printf("%d", k);
	}
	_getch();
	return 0;
}
