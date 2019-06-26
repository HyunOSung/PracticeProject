#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;

int main()
{
	int a[5];
	int b = 0;

	for (int i = 0; i < 5; ++i)
	{		
		cin >> b;		
		a[i] = b;
		printf("%d\n", a[i]);
	}
	for (int i = 4; i >= 0; --i)
	{
		printf("%d\n", a[i]);
	}
//	printf("%d\n", &a);



	return 0;
}