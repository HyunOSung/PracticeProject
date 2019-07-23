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

	HWND GetWindowHandle() const { return hwnd; }	// ���ٸ� �ϰ� ������ �Ұ����ϵ���
	UINT GetScreenWidth() const { return screenWidth; }
	UINT GetScreenHeight() const { return screenHeight; }
	LPCTSTR GetApplicationName() const { return applicationName; }

protected:
	HWND hwnd;				//������ �ڵ鰪
	HINSTANCE hinstance;	//â �ν��Ͻ�
	UINT screenWidth;		//â ����
	UINT screenHeight;		//â ����
	LPCTSTR applicationName;//�� �̸�
	DWORD windowStyle;		//â ��� ��Ÿ��

};

