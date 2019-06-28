#include <stdio.h>
#include<iostream>
#include<time.h>

using namespace std;


//해보고 싶은 것들
//1. 큐를 구현해서 탐색 경로 순으로 인쇄
//2. 랜덤하게 시작점과 탈출점 변경
//3. 배열 세트 여러가지를 만들어서 랜덤하게 4방향 배치한 맵 만들기
//4. 키 만들어서 획득하고 탈출하는 로직 만들기
//5. 콘솔 상에서 실시간으로 탐색하는 것 볼 수 있게 시각화 하기



#define Size 20

//맵에 배치될 오브젝트들의 종류 열거
#define WAY 0
#define	WALL 1
#define	ROUTE 2
#define	BLOCKED 3
#define	START 4
#define GOAL 7
#define	END 9

//미로찾기 상태 표시
bool start = false;
bool escape = false;
bool stuck = false;


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
		//배열 범위 밖일 경우 탈출
		return false;
	}
	else if (MapData[y][x] == END)
	{
		//탈출점 도착하면 탈출
		MapData[y][x] = GOAL;
		return true;
	}
	else if (MapData[y][x] != WAY)
	{
		//길이 아닐 경우 
		return false;
	}
	else
	{
		// 이동
		MapData[y][x] = ROUTE;
		if (SearchPath(x-1, y) ||
			SearchPath(x, y+1) ||
			SearchPath(x, y-1) ||
			SearchPath(x+1, y))
		//if (SearchPath(x - 1, y) ||
		//	SearchPath(x, y - 1) ||
		//	SearchPath(x + 1, y) ||
		//	SearchPath(x, y + 1))
		{
			return true;
		}
		else
		{
			//막다른 길 표시
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
	cout << "------------탈출 경로-------------" << endl;
	//탈출경로 인쇄
	
	for (int i = 0; i < Size; ++i)
	{
		for (int j = 0; j < Size; ++j)
		{
			if (MapData[i][j] == ROUTE)
			{				
				cout << "{" << i << " , " << j << "}" << endl;
			}
			else if (MapData[i][j] == GOAL)
			{
				cout << "{" << i << " , " << j << "}" << "탈출지점입니다. " << endl;
				break;
			}
		}
	}

	return  0;
}

int main()
{
	srand((unsigned int)time(0));

	//시작 좌표 설정
	int startingX = 0;
	int startingY = 0;

	//탈출 좌표 설정
	int escapeX = 19;
	int escapeY = 19;

	PointSetting(rand()%4,startingX ,startingY ); //시작지점 설정
	PointSetting(END, escapeY, escapeX);  //탈출지점 설정

	SearchPath(startingY, startingX);
	PrintMap();
	PrintOutEscapeRoute();
	
	
}