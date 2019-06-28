#include <stdio.h>
#include<iostream>

using namespace std;

#define Size 10

//�ʿ� ��ġ�� ������Ʈ���� ���� ����
#define WAY 0
#define	WALL 1
#define	ROUTE 2
#define	BLOCKED 3
#define	START 4
#define	END 9

//�̷�ã�� ���� ǥ��
bool start = false;
bool escape = false;
bool stuck = false;


int MapData[Size][Size] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 0, 1, 1, 0, 1, 1, 1},
	{1, 1, 1, 0, 1, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 1, 0, 1, 1, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
	{0, 1, 0, 1, 0, 1, 1, 0, 1, 1},
	{1, 1, 0, 1, 0, 1, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 0}
};




//enum class Move
//{
//	//�迭 Ž���� �� �̵��� ���� ����
//	LEFT = 0,
//	UP = 1,
//	RIGHT = 2,
//	DOWN = 3
//};

int PointSetting(int Object, int y, int x)
{
	//����, Ż��, �̿� ��Ÿ ������Ʈ ���ÿ� �Լ�
	switch (Object)
	{
	case 9:
		MapData[y][x] = END;
		break;
	}
	return  0;
}

bool SearchPath(int x, int y)
{
	if (x<0 || y<0 || x>Size-1 || y>Size-1)
	{
		cout << "���� Ȯ�� 1" << endl;
		//�迭 ���� ���� ��� Ż��
		return false;
	}
	else if (MapData[y][x] != WAY)
	{
		cout << "���� Ȯ�� 2" << endl;
		return false;
	}
	else if (MapData[y][x] == END)
	{
		cout << "���� Ȯ�� 3" << endl;
		MapData[y][x] = ROUTE;
		return true;
	}
	else
	{
		
		MapData[y][x] = ROUTE;
		if (SearchPath(y, x+1) ||
			SearchPath(y+1, x) ||
			SearchPath(y-1, x) ||
			SearchPath(y, x-1))
		{
			cout << "���� Ȯ�� 4" << endl;
			return true;
		}
		else
		{
			cout << "���� Ȯ�� 5" << endl;
			MapData[y][x] = BLOCKED;
			return false;
		}
	}
	return true;
}


int PrintMap()
{
	for (int i = 0; i < Size; ++i)
	{
		for (int j = 0; j < Size; ++j)
		{
			cout << MapData[i][j] << " ";
		}
		cout << endl;
	}
	return  0;
}

int PrintOutEscapeRoute()
{
	//Ż���� �μ�


	return  0;
}


int main()
{
	//���� ��ǥ ����
	int startingX = 0;
	int startingY = 0;

	//Ż�� ��ǥ ����
	int escapeX = 9;
	int escapeY = 9;

	//PointSetting(START, startingX, startingY); //�������� ����
	PointSetting(END, escapeY, escapeX);  //Ż������ ����

	SearchPath(startingY, startingX);
	PrintMap();
}