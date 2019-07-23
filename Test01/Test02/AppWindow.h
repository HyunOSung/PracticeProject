#pragma once
#include <Windows.h>

class Engine;

class AppWindow
{
public:
	AppWindow(HINSTANCE hinstance);
	~AppWindow();

	int Run(Engine* engine);
	bool InitializeWindow();
	virtual LRESULT MessageProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND GetWindowHandle() const { return hwnd; }	// 접근만 하고 수정은 불가능하도록
	UINT GetScreenWidth() const { return screenWidth; }
	UINT GetScreenHeight() const { return screenHeight; }
	LPCTSTR GetApplicationName() const { return applicationName; }

protected:
	HWND hwnd;				//윈도우 핸들값
	HINSTANCE hinstance;	//창 인스턴스
	UINT screenWidth;		//창 가로
	UINT screenHeight;		//창 세로
	LPCTSTR applicationName;//앱 이름
	DWORD windowStyle;		//창 모양 스타일

};

