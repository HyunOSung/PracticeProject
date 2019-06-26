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

//���� ��ġ���� ������ ������� �̸� �̵��غ��� �̵� �������� �˷���
bool CanMove(Vector2& Current)
{
	Vector2 Next;

	//4���� �����̱�
	for (int dir = (int)Direction::Right; dir <= (int)Direction::Up; ++dir)
	{
		Next = Current;
		Next = Next + Dir[dir]; // ���� �̵�, Right->Down->Left->Up

		if (Next.x < 0 || Next.y < 0 || Next.x >= MAX || Next.y >= MAX) //�̵��� ���� ��Ȯ���� üũ
		{
			//������� ���� ���� �̵�
			continue;
		}

		if (maze[Next.y][Next.x] == WAY) // �̸� ������ ���� �� �� �ִ� ������?
		{
			Current = Next;

			return true;
		}
	}
	return false; //���� �� ���� ����
}



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


//bool SearchMaze(int x, int y)
//{
//	if (x<0 || y<0 || x>MAX - 1 || y>MAX - 1)//�迭 ���� üũ
//	{
//		printf("���� üũ Ż��");
//		return false;
//	}
//	else
//	{
//		while (goal == false)
//		{
//			if (maze[y][x + 1] == WAY)
//			{
//				printf("���� üũ \n");
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

	//�������� ���� �ʱ�ȭ
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


	//�˰��� ����
	while (true)
	{
		maze[Current.y][Current.x] = PATH; // ������ġ ������ ǥ��
		if (Current.x == MAX - 1 && Current.y == MAX - 1)
		{
			//������ �����ϸ� ��
			break;
		}
		else if(CanMove(Current)) //���� ��ġ �̵��غ���
		{
			//���� ��ġ�� ������
			//���� ��ġ ���
			EscapeMap.push(Current);
		}
		else
		{
			if (EscapeMap.empty())
			{
				cout << "Ż��Ұ�" << endl;
				break;
			}
			else
			{
				maze[Current.y][Current.x] = BLOCK; //���� ��ġ�� �� ����
				Current = EscapeMap.top();//������ġ ����
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

	//1. ť �����
	//ó�� ���� ��ġ�� (���ڸ� ����, 100)
	//ó�� �ʱ�ȭ Ż�ⱸ ��ã��
	//Ž��(ť�� ������� ������)
	//{
	//	ť���� ���� ������(���� ��ġ)
	//	���� ��������
	//	4���� �̵�(�ݺ���)
	//	{
	//		�̵�����()
	//		{
	//			���� ��ġ�� ���� ���� +1 ���ֱ�
	//			���� ��ġ�� ��������?
	//			{
	//				��
	//				Ż�� ����
	//				
	//			}
	//			ť�� ���� ��ġ ���
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