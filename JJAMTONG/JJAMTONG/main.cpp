#include<iostream>
#include<stdio.h>

using namespace std;



//1. int main���� �־��µ� ���ο��� ����� ���ڸ� �������� ��� �ؾ� �ϴ���. :%f�� ���� �� �ִ�.
//2. ��ĵF�� ������ ��Ƽ������ ���ڷ� �޴��� : % �����ڷ� �پ��ϰ� ���� �� �ִ�. ���۷����� �˾Ƽ� ã�ƺ� ��
//3. scanf�� �ٸ� ���¸� �޴� ����� ������ �ִ��� : ���� ����.
//4. ***���������ʹ� ����� ���� ���� ����. ���ʿ� �Ⱦ��°� ���� ����
//5. ������ ���� �ּҸ� ���� �� ���� ����.


//���� �Է� �ް� 1���� �Է¹��� ���� �� ���ϱ�
//���ڿ� �Ųٷ� ���(string, char*)
//10������ 2������ ĳ����

//int sum(int n) //�Է¹��� �� �� ���ϱ�
//{	
//	if (n == 0)
//	{
//		return 0;
//	}
//	else
//	{
//		cout << n << endl;
//		return n+ sum(n-1);
//	}
//}


//�Ǻ���ġ ��ͷ� ���ϱ�
//int Fibo(int n)
//{
//
//	if (n == 0)
//	{
//		return 0;
//	}
//	else if (n==1)
//	{
//		return 1;
//	}
//	else
//	{
//		return Fibo(n - 1) + Fibo(n - 2);
//	}
//
//}

//10���� 2���� ��ȯ

//void Binary(int n)
//{
//	if (n < 2)
//	{
//		cout << n;
//	}
//	else
//	{
//		Binary(n / 2);
//		cout << (n % 2);
//
//		//�������� 2�� ���� �� �ٷ� ����ϸ� 2������ ��
//	}
//}


////���ڿ� �������
//void ReversePrint(const char* s)
//{
//	if (s[0] == '\0')
//	{
//		return;
//	}
//	else
//	{
//		ReversePrint(&s[1]);
//
//		cout << s[0];
//	}
//}

//Ž��
//Ž�� ���� �� ã�� �ε���
//���н� -1 ����
//for ������ �����غ���
//�Ϲ� �ݺ���
//int Search(int* Data, int Size, int Target)
//{
//	for (int i = 0; i < Size; ++i)
//	{
//		if (Data[i] == Target)
//		{
//			return Data[i];
//		}
//	}
//	return -1;
//}

//int Search2(int* Data, int Begin, int End, int Target)
//{
//	if (Data[Begin] == Target)
//	{
//
//		return Begin;
//	}
//	else if (Data[Begin] == Data[End])
//	{
//		return -1;
//	}
//	else
//	{
//		Search2(Data, Begin + 1, End, Target);
//	}
//
//
//}


int BinarySearch(int* Data, int Begin, int End, int Target)
{
	if (Begin > End)
	{
		return -1;
	}
	else
	{
		int Middle = (Begin + End) / 2;
		if (Data[Middle] == Target)
		{
			return  Middle;
		}
		if (Data[End] == Target) //����� �˻� ���ڰ� ������ Ž��
		{
			return End;
		}
		BinarySearch(Data, Begin, Middle - 1, Target); // �̵� ���� �� ���� ���� ã�� ��
		BinarySearch(Data, Middle + 1, End, Target); //�̵� ���� �� ū ���� ã�� ��
	}
}

int main()
{
	//int a = 5;
	//int* b = &a;
	//int c = 4;
	//int* d = &c;
	//int e = *b;
	//
	////int f = Punk(d);

	//printf("%d",a==e);

	//int a = 0;

	//cin >> a;



	//cout << sum(a) << endl;

	//return 0;


	//�Ǻ���ġ ���� ���ϱ�
	//int a = 0;
	//cin >> a;

	//cout << Fibo(a) << endl;

	//10���� 2���� ��ȯ
	//Binary(5);
	//return 0;


	//���ڿ� ���� ���
	//ReversePrint("Hello");
	//return 0;

	int Data[10] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << BinarySearch(Data, 0, 9, 8);
}


//int Punk(int *p)
//{
//	*p = 5;
//
//	return *p;
//}