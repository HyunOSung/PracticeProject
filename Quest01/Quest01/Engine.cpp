#include "Engine.h"
#include<stdio.h>
#include"Map.h"


Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Init()
{
	printf("�������� \n");
	Start();
}

void Engine::Start()
{
	printf("���� �۵� ���� \n");
	Map* map = new Map();
	Tick();
}

void Engine::Tick()
{
	printf("���� �۵��� \n");
	Term();
}

void Engine::Input()
{
}

void Engine::Render()
{
	


}

void Engine::Term()
{
	
	printf("�������� \n");
	
}
