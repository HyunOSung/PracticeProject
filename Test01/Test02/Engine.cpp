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
	//카메라 정보 설정
	cameraPosition = XMVectorSet(0.0f, 00.0f, -0.2f, 0.0f);
	cameraView = XMVectorSet(0.0f, 0.0f, 30.0f, 0.0f);
	cameraVector = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//뷰 행렬 선언
	XMMATRIX view = XMMatrixLookAtLH(cameraPosition, cameraView, cameraVector);

	//투영 행렬 선언(시야각, 종횡비 설정)
	float fovY = XMConvertToRadians(90.0f); // pi를 180도로 나눔
	float aspectRatio = static_cast<float>(window->GetScreenWidth() / static_cast<float>(window->GetScreenHeight())); // 종횡비 설정

	XMMATRIX projection = XMMatrixPerspectiveFovLH(fovY, aspectRatio, 1.0f, 100.0f); //투영 행렬(카메라 시야각, 화면 종횡비)

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
	if (IsError(result, TEXT("씬 상수 버퍼 생성 실패")))
	{
		return false;
	}

	return true;
}
