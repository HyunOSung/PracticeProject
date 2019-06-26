#include<stdio.h>
#include<iostream>
#include<stack>

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
		{1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 },
		{1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,1 },
		{1 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 },
		{1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
		{1 ,0 ,0 ,1 ,1 ,0 ,1 ,1 ,0 ,1 },
		{1 ,1 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,1 },
		{1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
		{1 ,1 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 }
};


class Vector2
{
public:
	Vector2() : x(0), y(0) {}
	int x;
	int y;


	Vector2 operator+(const Vector2& RightHandSide)
	{
		Vector2 Result;
		Result.x = this->x + RightHandSide.x;
		Result.y = this->y + RightHandSide.y;
	}
};

enum class Direction
{
	Right = 0,
	Down = 1,
	Left = 2,
	Up = 3
};

Vector2 Dir[4];

//현재 위치에서 일정한 방법으로 미리 이동해보고 이동 가능한지 알려줌
bool CanMove(Vector2& Current)
{
	Vector2 Next;

	//4방향 움직이기
	for (int dir = (int)Direction::Right; dir <= (int)Direction::Up; ++dir)
	{
		Next = Current;
		Next = Next + Dir[dir]; // 방향 이동, Right->Down->Left->Up

		if (Next.x < 0 || Next.y < 0 || Next.x >= MAX || Next.y >= MAX) //이동할 곳이 정확한지 체크
		{
			//현재방향 다음 방향 이동
			continue;
		}

		if (maze[Next.y][Next.x] == WAY) // 미리 가보는 곳이 갈 수 있는 곳인지?
		{
			Current = Next;

			return true;
		}
	}
	return false; //다음 갈 곳이 없음
}



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


//bool SearchMaze(int x, int y)
//{
//	if (x<0 || y<0 || x>MAX - 1 || y>MAX - 1)//배열 범위 체크
//	{
//		printf("진입 체크 탈출");
//		return false;
//	}
//	else
//	{
//		while (goal == false)
//		{
//			if (maze[y][x + 1] == WAY)
//			{
//				printf("진입 체크 \n");
//
//				maze[y][x] = PATH;
//				x++;
//			}
//			if (maze[y + 1][x] == WAY)
//			{
//				maze[y][x] = PATH;
//				y++;
//			}
//			if (maze[y][x - 1] == WAY)
//			{
//				maze[y][x] = PATH;
//				x--;
//			}
//			if (maze[y - 1][x] == WAY)
//			{
//				maze[y][x] = PATH;
//				y--;
//			}
//			else
//			{
//				if (maze[y][x + 1] == PATH)
//				{
//					maze[y][x] = BLOCK;
//					x++;
//				}
//				if (maze[y + 1][x] != PATH)
//				{
//					maze[y][x] = BLOCK;
//					y++;
//				}
//				if (maze[y][x - 1] != PATH)
//				{
//					maze[y][x] = BLOCK;
//					x--;
//				}
//				if (maze[y - 1][x] != PATH)
//				{
//					maze[y][x] = BLOCK;
//					y--;
//				}
//			}
//
//			if (maze[y][x] == maze[MAX - 1][MAX - 1])
//			{
//				goal = true;
//			}
//		}
//	}
//}




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

	//방향정보 매핑 초기화
	Dir[(int)Direction::Right].x = 1;
	Dir[(int)Direction::Right].y = 0;
	Dir[(int)Direction::Down].x = 0;
	Dir[(int)Direction::Down].y = 1;
	Dir[(int)Direction::Left].x = -1;
	Dir[(int)Direction::Left].y = 0;
	Dir[(int)Direction::Up].x = 0;
	Dir[(int)Direction::Up].y = -1;

	Vector2 Current;

	stack<Vector2> EscapeMap;


	//알고리즘 시작
	while (true)
	{
		maze[Current.y][Current.x] = PATH; // 현재위치 지도에 표시
		if (Current.x == MAX - 1 && Current.y == MAX - 1)
		{
			//목적지 도착하면 끝
			break;
		}
		else if(CanMove(Current)) //다음 위치 이동해보기
		{
			//다음 위치가 생겼음
			//현재 위치 기록
			EscapeMap.push(Current);
		}
		else
		{
			if (EscapeMap.empty())
			{
				cout << "탈출불가" << endl;
				break;
			}
			else
			{
				maze[Current.y][Current.x] = BLOCK; //현재 위치는 길 막힘
				Current = EscapeMap.top();//이전위치 복원
				EscapeMap.pop();
			}
		}
	}

	for (int y = 0; y < MAX; ++y)
	{
		for (int x = 0; x < MAX; ++x)
		{
			cout << maze[y][x] << " ";
		}
		cout << endl;
	}


	//{ 100, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
	//{ 1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 },
	//{ 1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,1 },
	//{ 1 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 },
	//{ 1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
	//{ 1 ,0 ,0 ,1 ,1 ,0 ,1 ,1 ,0 ,1 },
	//{ 1 ,1 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,1 },
	//{ 1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
	//{ 1 ,1 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 },
	//{ 1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 }

	//1. 큐 만들기
	//처음 현재 위치에 (숫자를 적음, 100)
	//처음 초기화 탈출구 몾찾음
	//탐색(큐가 비어있지 않으면)
	//{
	//	큐에서 정보 꺼내기(현재 위치)
	//	레벨 가져오기
	//	4방향 이동(반복문)
	//	{
	//		이동가능()
	//		{
	//			다음 위치에 현재 레벨 +1 써주기
	//			다음 위치가 목적지냐?
	//			{
	//				끝
	//				탈출 했음
	//				
	//			}
	//			큐에 다음 위치 기록
	//		}
	//	}
	//
	//
	//}


	////FindMaze(0, 0);
	//SearchMaze(0, 0);
	//PrintMap();

	return 0;
}