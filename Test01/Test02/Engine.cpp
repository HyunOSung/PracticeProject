#include "Engine.h"

Engine::Engine(HINSTANCE hinstance) : DXApp(hinstance)
{

}

Engine::~Engine()
{
	vertexShader->Release();
	Memory::SafeDelete(vertexShader);

	pixelShader->Release();
	Memory::SafeDelete(pixelShader);

	Memory::SafeDelete(mesh);
}

bool Engine::Init()
{
	if (DXApp::Init() == false)
	{
		return false;
	}

	if (InitializeScene() == false)
	{
		return false;
	}

	if (InitializeTransformation() == false)
	{
		return false;
	}

	return true;
}

int Engine::Run()
{
	return window->Run(this);
}

void Engine::Update()
{
	mesh->Update(deviceContext);
	deviceContext->VSSetConstantBuffers(1, 1, &constantBuffer);
}

void Engine::Render()
{
	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	deviceContext->ClearRenderTargetView(renderTargetView, color);	

	vertexShader->BindShader(deviceContext);
	pixelShader->BindShader(deviceContext);

	//pixelShader->BindSamplerState(deviceContext);
	//pixelShader->BindTexture(deviceContext);

	mesh->RenderBuffers(deviceContext);
	
	
	swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
	vertexShader = new VertexShader(TEXT("Shader/VS.fx"));
	if (vertexShader->CompileShader(device) == false)
	{
		return false;
	}

	if (vertexShader->CreateShader(device) == false)
	{
		return false;
	}

	pixelShader = new PixelShader(TEXT("Shader/PS.fx"));
	if (pixelShader->CompileShader(device) == false)
	{
		return false;
	}

	if (pixelShader->CreateShader(device) == false)
	{
		return false;
	}

	//if (pixelShader->LoadTexture(device, TEXT("Resource/Texture/image01.jpg")) == false)
	//{
	//	return false;
	//}

	//if (pixelShader->CreateSamplerState(device) == false)
	//{
	//	return false;
	//}
	
	mesh = new Mesh(0.0f, 0.0f, 0.0f);
	if (mesh->InitializeBuffers(device, vertexShader->GetShaderBuffer()) == false)
	{
		return false;
	}

	return true;
}

bool Engine::InitializeTransformation()
{
	//ī�޶� ���� ����
	cameraPosition = XMVectorSet(0.0f, 00.0f, -0.2f, 0.0f);
	cameraView = XMVectorSet(0.0f, 0.0f, 30.0f, 0.0f);
	cameraVector = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//�� ��� ����
	XMMATRIX view = XMMatrixLookAtLH(cameraPosition, cameraView, cameraVector);

	//���� ��� ����(�þ߰�, ��Ⱦ�� ����)
	float fovY = XMConvertToRadians(90.0f); // pi�� 180���� ����
	float aspectRatio = static_cast<float>(window->GetScreenWidth() / static_cast<float>(window->GetScreenHeight())); // ��Ⱦ�� ����

	XMMATRIX projection = XMMatrixPerspectiveFovLH(fovY, aspectRatio, 1.0f, 100.0f); //���� ���(ī�޶� �þ߰�, ȭ�� ��Ⱦ��)

	PerSceneBuffer matrixData;
	matrixData.view = XMMatrixTranspose(view);
	matrixData.projection = XMMatrixTranspose(projection);

	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.ByteWidth = sizeof(PerSceneBuffer);
	cbDesc.CPUAccessFlags = 0;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(D3D11_SUBRESOURCE_DATA));
	cbData.pSysMem = &matrixData;

	HRESULT result = device->CreateBuffer(&cbDesc, &cbData, &constantBuffer);
	if (IsError(result, TEXT("�� ��� ���� ���� ����")))
	{
		return false;
	}

	return true;
}
