#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;

int main()
{

	//최소 공배수 구하기
	//입력 2개 받아서 두 수의 최소 공배수를 구하라.

	int a;
	int b;

	bool EndA = false;
	bool EndB = false;
	bool EndCal = false;


	int multiSetA[10][2] = {};
	int multiSetB[10][2] = {};

	cout << "첫번째 정수를 입력하세요.";
	cin >> a;

	cout << "두번째 정수를 입력하세요.";
	cin >> b;

	int i = 2;
	int j = 0;

	int k = 2;
	int e = 1;

	int l = 0;
	int r = 1;

	int result = 1;

	// 정수 입력 받아서 나누기
	while (EndA == false)
	{		
		if (a%i == 0)
		{		
			a = a / i;
			multiSetA[j][0] = i;
			if (multiSetA[j][0] == i)
			{
				multiSetA[j][1] += 1;
			}
		}
		else if (i%2 != 0) //i가 2의 배수가 아니라면 1 더하기
		{
			i++;
		}
		else
		{
			i++;
			j++;
		}

		if (a == 1)
		{
			EndA = true;
		}
	}

	while (EndB == false)
	{
		if (b%k == 0)
		{
			b = b / k;
			multiSetB[l][0] = k;
			if (multiSetB[l][0] == k)
			{
				multiSetB[l][1] += 1;
			}
		}
		else if (k % 2 != 0) //i가 2의 배수가 아니라면 1 더하기
		{
			k++;
		}
		else
		{
			k++;
			l++;
		}

		if (b == 1)
		{
			EndB = true;
		}
	}
	// 배열 두 개 비교해서 ,0이 같으면 1비교, 1비교에서 더 높은쪽 인수를 반복문 진입으로 곱

	int m = 0;
	int n = 0;


	while (EndCal == false)
	{
		if (multiSetA[m][0] == multiSetB[n][0]) //같은 수가 있다면
		{
			if (multiSetA[m][1] >= multiSetB[n][1])
			{
				for (int i = 0; i < multiSetA[m][1]; ++i)
				{
					result *= multiSetA[m][0];
				}
				m++;
				n++;
			}
			else
			{
				for (int i = 0; i < multiSetB[m][1]; ++i)
				{
					result *= multiSetA[m][0];
				}
				m++;
				n++;
			}
		}
		else if (multiSetA[m][0] != multiSetB[n][0]) //같은수가 없다면
		{
			for (int i = 0; i < multiSetA[m][1]; ++i)
			{
				result *= multiSetA[m][0];
			}
			for (int i = 0; i < multiSetB[m][1]; ++i)
			{
				result *= multiSetA[m][0];
			}

			m++;
			n++;
		}

		if (multiSetA[m][0] == 0)
		{

			cout << result << endl;
			EndCal = true;
			break;
		}
	}
}
