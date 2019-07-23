#include "AppWindow.h"
#include "Engine.h"

AppWindow* app = NULL;

LRESULT CALLBACK WindowProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (app != NULL)// ȭ���� ���� �޽����� ������ �� ����
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
	//�ۿ� ���� �з�����
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
	//â ����ü �� ����.
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŀ��
	wc.hbrBackground = NULL;				//���.
	wc.lpszClassName = TEXT("Test02");	//â Ŭ���� �̸�.
	wc.lpfnWndProc = WindowProcessor;		//�޽��� ó���Լ�

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	hwnd = CreateWindow(wc.lpszClassName, applicationName, windowStyle, 0, 0, screenWidth, screenHeight, NULL, NULL, hinstance, NULL);

	if (hwnd == NULL)	//�ڵ� ����⿡ �����ϸ� NULL���� ���.
	{
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);

	return true;
}

LRESULT AppWindow::MessageProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Ű�Է�, esc �Է¹����� �˾��ڽ� ���� ���� �޽��� ���
	switch (msg)
	{
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				if (MessageBox(NULL, TEXT("�����Ͻðڽ��ϱ�?"), TEXT("����"), MB_YESNO | MB_ICONQUESTION) == IDYES)
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
