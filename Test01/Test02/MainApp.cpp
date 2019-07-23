#pragma once
#include "Engine.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	Engine engine(hinstance);
	if (engine.Init() == false)
	{
		return 0;
	}

	return engine.Run();
}