#include "AppWindow.h"
#include "Engine.h"

AppWindow* app = NULL;

LRESULT CALLBACK WindowProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (app != NULL)// 화면이 떠야 메시지를 전달할 수 있음
	{
		return app->MessageProcessor(hwnd, msg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

AppWindow::AppWindow(HINSTANCE hinstance)
{
	//앱에 들어가는 패러미터
	hwnd = NULL;
	this->hinstance = hinstance;
	screenWidth = 1600;
	screenHeight = 900;
	applicationName = TEXT("Test08 - Texture Mapping");
	windowStyle = WS_OVERLAPPEDWINDOW;
	app = this;

}

AppWindow::~AppWindow()
{
}

int AppWindow::Run(Engine * engine)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			engine->Update();
			engine->Render();
		}
	}

	return 0;
}

bool AppWindow::InitializeWindow()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	//창 구조체 값 설정.
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//아이콘
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//커서
	wc.hbrBackground = NULL;				//배경.
	wc.lpszClassName = TEXT("Test02");	//창 클래스 이름.
	wc.lpfnWndProc = WindowProcessor;		//메시지 처리함수

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	hwnd = CreateWindow(wc.lpszClassName, applicationName, windowStyle, 0, 0, screenWidth, screenHeight, NULL, NULL, hinstance, NULL);

	if (hwnd == NULL)	//핸들 만들기에 실패하면 NULL값을 출력.
	{
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);

	return true;
}

LRESULT AppWindow::MessageProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//키입력, esc 입력받으면 팝업박스 띄우고 종료 메시지 출력
	switch (msg)
	{
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				if (MessageBox(NULL, TEXT("종료하시겠습니까?"), TEXT("종료"), MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					DestroyWindow(this->hwnd);
				}
			}
		}
			return 0;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
			return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
