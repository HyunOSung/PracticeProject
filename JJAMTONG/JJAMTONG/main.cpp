#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;

int main()
{
	int a = 10000;
	float pi = 0;

	for (int j = 0; j < 10; ++j)
	{

		printf("%d\n", a);
		pi = 0;
		for (int i = 0; i < a + 1; ++i)
		{
			float var = 1.0f / ((2.0f*(float)i) + 1.0f);
			if (i % 2 == 0)
			{
				pi = pi + var;
			}
			else
			{
				pi = pi - var;
			}
			if (i != 0 && i % a == 0)
			{
				printf("%f\n", 4.0f * pi);
			}
		}

		a = a + 10000;
	}
	return 0;
}