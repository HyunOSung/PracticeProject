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
	int m = 0;

	int q = 1;


	// ���� �Է� �޾Ƽ� ������
	while (EndA == false)
	{
		
		if (a%i == 0)
		{		
			a = a / i;
			multiSetA[j][0] = i;
			cout << multiSetA[0][0] << endl;
			if (multiSetA[j][0] == i)
			{
				cout << multiSetA[0][1] << endl;
				multiSetA[j][1] += 1;

			}
			else if (i != multiSetA[j][0])
			{					
				j++;
			}
			cout << a << endl;
		}
		else
		{
			i++;
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
			b= b / k;
			multiSetB[l][0] = k;
			if (k == multiSetB[l][0])
			{
				multiSetB[l][1] += 1;

			}
			else if (k != multiSetB[l][0])
			{
				
				l++;
			}
		}
		else
		{
			k++;
		}



		if (b == 1)
		{
			EndB = true;
		}
	}
	// �迭 �� �� ���ؼ� ,0�� ������ 1��, 1�񱳿��� �� ������ �μ��� �ݺ��� �������� ��

	

	while (EndCal == false)
	{//�迭 [][0]���ڰ� ���� ���
		if (multiSetA[m][0] == multiSetB[m][0])
		{
			if (multiSetA[m][1] >= multiSetB[m][1])
			{
				cout << multiSetA[0][1]  << endl;
				for (int n = multiSetA[m][1]; n < multiSetA[m][1]; ++n)
				{
					
					q *= multiSetA[m][0];
				}
			}
			else
			{
				for (int n = multiSetB[m][1]; n < multiSetB[m][1]; ++n)
				{
					q *= multiSetB[m][0];
				}
			}
		}
		else if (multiSetA[m][0] != multiSetB[m][0])
		{

			for (int n = multiSetA[m][1]; n < multiSetA[m][1]; ++n)
			{
				q *= multiSetA[m][0];
			}

			for (int n = multiSetB[m][1]; n < multiSetB[m][1]; ++n)
			{
				q *= multiSetB[m][0];
			}
		}
		
		if (multiSetA[m][0] && multiSetB[m][0] == 0)
		{
			cout << q << endl;
			EndCal = true;
		}


		m++;
		cout << m << endl;
	}






}
