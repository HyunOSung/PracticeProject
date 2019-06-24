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
	printf("엔진생성 \n");
	Start();
}

void Engine::Start()
{
	printf("엔진 작동 시작 \n");
	Map* map = new Map();
	Tick();
}

void Engine::Tick()
{
	printf("엔진 작동중 \n");
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
	
	printf("엔진삭제 \n");
	
}
