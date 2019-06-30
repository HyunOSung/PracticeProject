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


const int QueueSize = 111; //배열 범위 설정
int Data[QueueSize][2] = {}; // 루트 추적할 배열 설정
int pY = 0; //배열 저장용 Y 좌표


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
		Data[pY][0] = { y };
		Data[pY][1] = { x };

		escape = true;
		
		//cout << Data[pY][0] << " " << Data[pY][1] << endl;
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
		{
			Data[pY][0] = { y };
			Data[pY][1] = { x };

			//cout << Data[pY][0] << endl;
			++pY;
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
	for (int i = 111; i < 0; --i)
	{
		cout << "반복문진입" << endl;
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
	//			cout << "{" << i << " , " << j << "}" << "탈출지점입니다. " << endl;
	//			break;
	//		}
	//	}
	//}
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

	//cout << Data[0][0] << "," << Data[0][3] << endl;

	PointSetting(rand()%4,startingX ,startingY ); //시작지점 설정
	PointSetting(END, escapeY, escapeX);  //탈출지점 설정



	SearchPath(startingY, startingX);
	PrintMap();
	PrintOutEscapeRoute();
	

}