#include<stdio.h>
#include"Engine.h"


int main()
{
	//���α׷� ����, �õ���


	Engine* engine = new Engine(); //Engine�� �޸� ����, �� ���� ����
	engine->Init(); //Engine ��ü ���� �޽���

	//engine->Term(); //Engine ��ü ���� �޽���
	delete engine; //Engine ��ü ����

}