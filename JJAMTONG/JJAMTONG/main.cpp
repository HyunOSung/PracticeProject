#include<iostream>
#include<stdio.h>

using namespace std;



//1. int main으로 넣었는데 내부에서 더블로 인자를 받으려면 어떻게 해야 하는지. :%f로 받을 수 있다.
//2. 스캔F는 무조건 인티저형만 인자로 받는지 : % 연산자로 다양하게 받을 수 있다. 레퍼런스는 알아서 찾아볼 것
//3. scanf로 다른 형태를 받는 방법은 무엇이 있는지 : 위와 동일.
//4. ***삼중포인터는 사용할 일이 거의 없다. 애초에 안쓰는게 좋은 설계
//5. 포인터 없이 주소를 가져 올 수는 없다.


//숫자 입력 받고 1부터 입력받은 숫자 합 구하기
//문자열 거꾸로 찍기(string, char*)
//10진수를 2진수로 캐스팅

//int sum(int n) //입력받은 수 합 구하기
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


//피보나치 재귀로 구하기
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

//10진수 2진수 변환

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
//		//나머지를 2로 나눈 걸 바로 출력하면 2진수가 됨
//	}
//}


////문자열 역순출력
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

//탐색
//탐색 성공 시 찾은 인덱스
//실패시 -1 리턴
//for 문으로 구현해보기
//일반 반복문
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
		if (Data[End] == Target) //가운데에 검색 숫자가 있으면 탐색
		{
			return End;
		}
		BinarySearch(Data, Begin, Middle - 1, Target); // 미들 보다 더 작은 수를 찾을 때
		BinarySearch(Data, Middle + 1, End, Target); //미들 보다 더 큰 수를 찾을 때
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


	//피보나치 수열 구하기
	//int a = 0;
	//cin >> a;

	//cout << Fibo(a) << endl;

	//10진수 2진수 변환
	//Binary(5);
	//return 0;


	//문자열 역순 출력
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