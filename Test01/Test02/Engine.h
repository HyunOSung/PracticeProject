#pragma once
#include "DXApp.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "PixelShader.h"


class Engine : public DXApp //���
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

	bool Init() override;	// ���� ����
	int Run();				// ���� �۵�
	void Update() override; // ȭ�� ������Ʈ
	void Render() override; // �׸���

private:
	bool InitializeScene(); // ������ �� �ʱ�ȭ
	bool InitializeTransformation(); //������ ī�޶� ������ ������Ʈ ��ġ �ʱ�ȭ

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	Mesh* mesh;

	ID3D11Buffer* constantBuffer; //�����, ������� ���� ����
	XMVECTOR cameraPosition;
	XMVECTOR cameraView;
	XMVECTOR cameraVector;

};

