#include <stdio.h>
#include<iostream>
#include<time.h>

using namespace std;


//�غ��� ���� �͵�
//1. ť�� �����ؼ� Ž�� ��� ������ �μ�
//2. �����ϰ� �������� Ż���� ����
//3. �迭 ��Ʈ ���������� ���� �����ϰ� 4���� ��ġ�� �� �����
//4. Ű ���� ȹ���ϰ� Ż���ϴ� ���� �����
//5. �ܼ� �󿡼� �ǽð����� Ž���ϴ� �� �� �� �ְ� �ð�ȭ �ϱ�



#define Size 20

//�ʿ� ��ġ�� ������Ʈ���� ���� ����
#define WAY 0
#define	WALL 1
#define	ROUTE 2
#define	BLOCKED 3
#define	START 4
#define GOAL 7
#define	END 9

//�̷�ã�� ���� ǥ��
bool start = false;
bool escape = false;
bool stuck = false;


const int QueueSize = 111; //�迭 ���� ����
int Data[QueueSize][2] = {}; // ��Ʈ ������ �迭 ����
int pY = 0; //�迭 ����� Y ��ǥ


double MapData[Size][Size] = {
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
	{ 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1 },
	{ 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 },
	{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
	{ 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1 },
	{ 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1 },
	{ 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 },
	{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0 }
};

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
		//�迭 ���� ���� ��� Ż��
		return false;
	}
	else if (MapData[y][x] == END)
	{
		//Ż���� �����ϸ� Ż��
		MapData[y][x] = GOAL;
		Data[pY][0] = { y };
		Data[pY][1] = { x };

		escape = true;
		
		//cout << Data[pY][0] << " " << Data[pY][1] << endl;
		return true;
	}
	else if (MapData[y][x] != WAY)
	{
		//���� �ƴ� ��� 
		return false;
	}
	else
	{
		// �̵�
		MapData[y][x] = ROUTE;
		if (SearchPath(x-1, y) ||
			SearchPath(x, y+1) ||
			SearchPath(x, y-1) ||
			SearchPath(x+1, y))
		{
			Data[pY][0] = { y };
			Data[pY][1] = { x };

			//cout << Data[pY][0] << endl;
			++pY;
			return true;
		}
		else
		{
			//���ٸ� �� ǥ��
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
	cout << endl;
	return  0;
}

int PrintOutEscapeRoute()
{
	cout << "------------Ż�� ���-------------" << endl;
	//Ż���� �μ�
	for (int i = 111; i < 0; --i)
	{
		cout << "�ݺ�������" << endl;
		cout << Data[i][0] << " " << Data[i][1] << endl;
	}

	//for (int i = 0; i < Size; ++i)
	//{
	//	for (int j = 0; j < Size; ++j)
	//	{
	//		if (MapData[i][j] == ROUTE)
	//		{				
	//			cout << "{" << i << " , " << j << "}" << endl;
	//		}
	//		else if (MapData[i][j] == GOAL)
	//		{
	//			cout << "{" << i << " , " << j << "}" << "Ż�������Դϴ�. " << endl;
	//			break;
	//		}
	//	}
	//}
	return  0;
}

int main()
{
	srand((unsigned int)time(0));

	//���� ��ǥ ����
	int startingX = 0;
	int startingY = 0;

	//Ż�� ��ǥ ����
	int escapeX = 19;
	int escapeY = 19;

	//cout << Data[0][0] << "," << Data[0][3] << endl;

	PointSetting(rand()%4,startingX ,startingY ); //�������� ����
	PointSetting(END, escapeY, escapeX);  //Ż������ ����



	SearchPath(startingY, startingX);
	PrintMap();
	PrintOutEscapeRoute();
	

}