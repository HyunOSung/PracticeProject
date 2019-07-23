#include "DXApp.h"



DXApp::DXApp(HINSTANCE hinstance)
{
	window = new AppWindow(hinstance);
}


DXApp::~DXApp()
{
	//소멸자에서 모든 메모리 해제
	Memory::SafeDelete(window);
	Memory::SafeRelease(device);
	Memory::SafeRelease(deviceContext);
	Memory::SafeRelease(swapChain);
	Memory::SafeRelease(renderTargetView);
}

bool DXApp::Init()
{
	//프로그램 시작 시에 창 만드는 함수를 실행, 실패시 false 출력
	if (window->InitializeWindow() == false)
	{
		return false;
	}

	if (InitializeDX3D() == false) //DX 초기화
	{
		return false;
	}

	return true;
}

bool DXApp::InitializeDX3D()
{
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;		//버퍼 개수
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//버퍼 용도
	swapDesc.OutputWindow = window->GetWindowHandle();
	swapDesc.Windowed = true;	//윈도우모드
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		// 버퍼 교체시 효과 여부
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//색상 체널 rgba 8비트씩(32비트) unsigned Normal
	swapDesc.BufferDesc.Width = window->GetScreenWidth();
	swapDesc.BufferDesc.Height = window->GetScreenHeight();

	swapDesc.SampleDesc.Count = 1;		// 안티엘라이싱 미사용
	swapDesc.SampleDesc.Quality = 0;	

	//스왑체인과 장치, 장치 문맥 생성.

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		NULL, 
		D3D_DRIVER_TYPE_HARDWARE, 
		NULL, 
		NULL, 
		NULL, 
		NULL, 
		D3D11_SDK_VERSION, 
		&swapDesc, 
		&swapChain, 
		&device, 
		NULL, 
		&deviceContext);

	if (FAILED(result))	//정의문. 0보다 작은 값이 나오면 오류.
	{
		MessageBox(NULL, TEXT("장치 생성 실패"), TEXT("오류"), MB_OK);
		return false;
	}

	ID3D11Texture2D* backBufferTexture;
	result = swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);	//메모리 할당

	if (FAILED(result))
	{
		MessageBox(NULL, TEXT("백 버퍼 생성 실패"), TEXT("오류"), MB_OK);
		return false;
	}

	result = device->CreateRenderTargetView(backBufferTexture, NULL, &renderTargetView);

	if (FAILED(result))
	{
		MessageBox(NULL, TEXT("렌더 타겟 생성 실패"), TEXT("오류"), MB_OK);
		return false;
	}

	//렌더 타겟 뷰 생성.
	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL); //출력을 병합하는 단계

	//버퍼 생성을 위해 사용했던 자원 해제.
	Memory::SafeRelease(backBufferTexture);

	SetViewPort();

	return true;
}

void DXApp::SetViewPort()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(window->GetScreenWidth());
	viewport.Height = static_cast<float>(window->GetScreenHeight());

	deviceContext->RSSetViewports(1, &viewport);
}
