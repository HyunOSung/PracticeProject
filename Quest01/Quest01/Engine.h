#pragma once
class Engine
{
public:
	Engine();
	~Engine();


	void Init();
	void Start();
	void Tick();
	void Input();
	void Render();
	void Term();


	bool bIsRunning = true; //엔진 작동 체크



};

