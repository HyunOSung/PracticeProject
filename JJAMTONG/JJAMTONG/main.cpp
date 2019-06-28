#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;


void Swap(int& a, int& b)
{
	int Temp = a;
	a = b;
	b = Temp;
}



void SelectionSort(int* Data, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			if (Data[i] > Data[j])
			{
				Swap(Data[i], Data[j]);
			}
		}
	}
}

void BubbleSort(int* Data, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			if (Data[i] > Data[j])
			{
				Swap(Data[i], Data[j]);
			}
		}
	}
}

int main()
{
	int Data[10] = { 10, 2, 12, 15, 16, 20, 49, 60, 3, 6 };

	for (int i = 0; i < 10; ++i)
	{
		cout << Data[i] << ", ";
	}
	cout << endl;

	SelectionSort(Data, 10);

	for (int i = 0; i < 10; ++i)
	{
		cout << Data[i] << ", ";
	}
	cout << endl;

