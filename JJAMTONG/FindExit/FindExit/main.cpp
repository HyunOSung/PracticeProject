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
//	if (x<0 || y<0 || x>MAX - 1 || y>MAX - 1)//배열 범위 체크
//	{
//		return false;
//	}
//	else if (maze[y][x] != WAY) // 벽체크
//	{
//		return false;
//	}
//	else if (x == MAX - 1 && y == MAX - 1) //목적지 체크, 탈출
//	{
//		maze[y][x] = PATH;
//		return true;
//	}
//	else // 이동
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
//			maze[y][x] = BLOCK;//못가는 길
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
		if (x<0 || y<0 || x>MAX - 1 || y>MAX - 1)//배열 범위 체크
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