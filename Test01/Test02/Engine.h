#pragma once
#include "DXApp.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "PixelShader.h"


class Engine : public DXApp //상속
{
private:
	struct PerSceneBuffer
	{
		PerSceneBuffer() { ZeroMemory(this, sizeof(this)); }

		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	Engine(HINSTANCE hinstance);
	~Engine();

	bool Init() override;	// 엔진 시작
	int Run();				// 엔진 작동
	void Update() override; // 화면 업데이트
	void Render() override; // 그리기

private:
	bool InitializeScene(); // 생성한 씬 초기화
	bool InitializeTransformation(); //생성한 카메라를 포함한 오브젝트 위치 초기화

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	Mesh* mesh;

	ID3D11Buffer* constantBuffer; //뷰행렬, 투영행렬 담을 버퍼
	XMVECTOR cameraPosition;
	XMVECTOR cameraView;
	XMVECTOR cameraVector;

};

