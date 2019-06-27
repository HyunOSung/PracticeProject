#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;

int main()
{
	int a[10];
	int b[10];
	bool q = false;
	bool w = false;
	bool e = false;

	int z = 0;


	for (int i = 0; i < 10; ++i)
	{
		cin >> a[i];
		b[i] = 0;
	}
	for (int j = 0; j < 10; j++)
	{
		for (int k = 0; k < j; k++)
		{
			if (a[k] == a[j])
			{
				q = true;
				break;
			}

		}
		if (q == true)
		{
			b[z] = a[j];
			z++;
		}

	}

	for (int l = 0; l<z; l++)
	{
		cout << b[l] << endl;

	}
	return 0;
}