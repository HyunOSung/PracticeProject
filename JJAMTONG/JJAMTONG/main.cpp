#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;

int main()
{

	//�ּ� ����� ���ϱ�
	//�Է� 2�� �޾Ƽ� �� ���� �ּ� ������� ���϶�.

	int a;
	int b;

	bool EndA = false;
	bool EndB = false;
	bool EndCal = false;


	int multiSetA[10][2] = {};
	int multiSetB[10][2] = {};

	cout << "ù��° ������ �Է��ϼ���.";
	cin >> a;

	cout << "�ι�° ������ �Է��ϼ���.";
	cin >> b;

	int i = 2;
	int j = 0;

	int k = 2;
	int e = 1;

	int l = 0;
	int r = 1;

	int result = 1;

	// ���� �Է� �޾Ƽ� ������
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
		else if (i%2 != 0) //i�� 2�� ����� �ƴ϶�� 1 ���ϱ�
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
		else if (k % 2 != 0) //i�� 2�� ����� �ƴ϶�� 1 ���ϱ�
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
	// �迭 �� �� ���ؼ� ,0�� ������ 1��, 1�񱳿��� �� ������ �μ��� �ݺ��� �������� ��

	int m = 0;
	int n = 0;


	while (EndCal == false)
	{
		if (multiSetA[m][0] == multiSetB[n][0]) //���� ���� �ִٸ�
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
		else if (multiSetA[m][0] != multiSetB[n][0]) //�������� ���ٸ�
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
