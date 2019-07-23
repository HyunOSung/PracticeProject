#include "DXApp.h"



DXApp::DXApp(HINSTANCE hinstance)
{
	window = new AppWindow(hinstance);
}


DXApp::~DXApp()
{
	//�Ҹ��ڿ��� ��� �޸� ����
	Memory::SafeDelete(window);
	Memory::SafeRelease(device);
	Memory::SafeRelease(deviceContext);
	Memory::SafeRelease(swapChain);
	Memory::SafeRelease(renderTargetView);
}

bool DXApp::Init()
{
	//���α׷� ���� �ÿ� â ����� �Լ��� ����, ���н� false ���
	if (window->InitializeWindow() == false)
	{
		return false;
	}

	if (InitializeDX3D() == false) //DX �ʱ�ȭ
	{
		return false;
	}

	return true;
}

bool DXApp::InitializeDX3D()
{
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;		//���� ����
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//���� �뵵
	swapDesc.OutputWindow = window->GetWindowHandle();
	swapDesc.Windowed = true;	//��������
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		// ���� ��ü�� ȿ�� ����
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//���� ü�� rgba 8��Ʈ��(32��Ʈ) unsigned Normal
	swapDesc.BufferDesc.Width = window->GetScreenWidth();
	swapDesc.BufferDesc.Height = window->GetScreenHeight();

	swapDesc.SampleDesc.Count = 1;		// ��Ƽ�����̽� �̻��
	swapDesc.SampleDesc.Quality = 0;	

	//����ü�ΰ� ��ġ, ��ġ ���� ����.

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

	if (FAILED(result))	//���ǹ�. 0���� ���� ���� ������ ����.
	{
		MessageBox(NULL, TEXT("��ġ ���� ����"), TEXT("����"), MB_OK);
		return false;
	}

	ID3D11Texture2D* backBufferTexture;
	result = swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);	//�޸� �Ҵ�

	if (FAILED(result))
	{
		MessageBox(NULL, TEXT("�� ���� ���� ����"), TEXT("����"), MB_OK);
		return false;
	}

	result = device->CreateRenderTargetView(backBufferTexture, NULL, &renderTargetView);

	if (FAILED(result))
	{
		MessageBox(NULL, TEXT("���� Ÿ�� ���� ����"), TEXT("����"), MB_OK);
		return false;
	}

	//���� Ÿ�� �� ����.
	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL); //����� �����ϴ� �ܰ�

	//���� ������ ���� ����ߴ� �ڿ� ����.
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
