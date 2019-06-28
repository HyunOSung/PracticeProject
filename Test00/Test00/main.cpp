#include <stdio.h>
#include<iostream>

using namespace std;

#define Size 10

//맵에 배치될 오브젝트들의 종류 열거
#define WAY 0
#define	WALL 1
#define	ROUTE 2
#define	BLOCKED 3
#define	START 4
#define	END 9

//미로찾기 상태 표시
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
//	//배열 탐색할 때 이동할 방향 설정
//	LEFT = 0,
//	UP = 1,
//	RIGHT = 2,
//	DOWN = 3
//};

int PointSetting(int Object, int y, int x)
{
	//시작, 탈출, 이외 기타 오브젝트 셋팅용 함수
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
		cout << "진입 확인 1" << endl;
		//배열 범위 밖일 경우 탈출
		return false;
	}
	else if (MapData[y][x] != WAY)
	{
		cout << "진입 확인 2" << endl;
		return false;
	}
	else if (MapData[y][x] == END)
	{
		cout << "진입 확인 3" << endl;
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
			cout << "진입 확인 4" << endl;
			return true;
		}
		else
		{
			cout << "진입 확인 5" << endl;
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
	//탈출경로 인쇄


	return  0;
}


int main()
{
	//시작 좌표 설정
	int startingX = 0;
	int startingY = 0;

	//탈출 좌표 설정
	int escapeX = 9;
	int escapeY = 9;

	//PointSetting(START, startingX, startingY); //시작지점 설정
	PointSetting(END, escapeY, escapeX);  //탈출지점 설정

	SearchPath(startingY, startingX);
	PrintMap();
}