#include<stdio.h>
#include<iostream>

using namespace std;

#define MAX 10
#define WAY 0
#define WALL 1
#define BLOCK 2
#define PATH 3

bool goal = false;

int maze[MAX][MAX] =
{
		{0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
		{1 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,1 },
		{1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 },
		{1 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,0 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 }

};


//bool FindMaze(int x, int y)
//{
//	if (x<0 || y<0 || x>MAX - 1 || y>MAX - 1)//�迭 ���� üũ
//	{
//		return false;
//	}
//	else if (maze[y][x] != WAY) // ��üũ
//	{
//		return false;
//	}
//	else if (x == MAX - 1 && y == MAX - 1) //������ üũ, Ż��
//	{
//		maze[y][x] = PATH;
//		return true;
//	}
//	else // �̵�
//	{
//		maze[y][x] = PATH;
//		if (FindMaze(x + 1, y))
//		{
//			return true;
//		}
//		else if (FindMaze(x, y + 1))
//		{
//			return true;
//		}
//		else if (FindMaze(x - 1, y))
//		{
//			return true;
//		}
//		else if (FindMaze(x, y - 1))
//		{
//			return true;
//		}
//		else
//		{
//			maze[y][x] = BLOCK;//������ ��
//			return false;
//		}
//
//	}
//	return true;
//}


int SearchMaze(int x, int y)
{
	while (goal)
	{
		if (x<0 || y<0 || x>MAX - 1 || y>MAX - 1)//�迭 ���� üũ
		{
			return false;
		}



		
	}
}



void PrintMap()
{
	for (int y = 0; y < MAX; ++y)
	{
		for (int x = 0; x < MAX; ++x)
		{
			cout << maze[y][x] << " ";
		}
		cout << endl;
	}
}


int main()
{
	//FindMaze(0, 0);
	SearchMaze(0, 0);
	PrintMap();
}