#pragma once
#include"DXUtil.h"

using namespace DirectX;

class Mesh
{
public:
	struct Vertex
	{
		XMFLOAT3 position; //정점 위치 정보 받을 객체
		XMFLOAT4 color;
		//XMFLOAT2 textureCoord;

		Vertex(float x, float y, float z) : position(x, y, z) {} // 정점정보들 position에 삽입
		Vertex(XMFLOAT3 position) : position(position) {}
		Vertex(XMFLOAT3 position, XMFLOAT4 color) : position(position), color(color) {}
		//Vertex(XMFLOAT3 position, XMFLOAT4 color, XMFLOAT2 uv) : position(position), color(color), textureCoord(uv) {}
	};

	struct PerObjectBuffer
	{
		PerObjectBuffer() { ZeroMemory(this, sizeof(this)); }
		XMMATRIX world;
	};

public:
	Mesh();
	Mesh(float x, float y, float z);
	~Mesh();

	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer);//버퍼 초기화

	void RenderBuffers(ID3D11DeviceContext* deviceContext); //버퍼 렌더링

	void Update(ID3D11DeviceContext* deviceContext);

	//Getter 추가
	XMFLOAT3 GetPosition() const { return position; }
	XMMATRIX GetWorldMatrix() const;

	//Setter
	void SetPosition(float x, float y, float z)
	{
		position = XMFLOAT3(x, y, z);
	}

private:
	int nVertices;						//정점 개수 변수
	int nIndices;						//인덱스 개수

	ID3D11Buffer* vertexBuffer;			//정점 버퍼 객체
	ID3D11Buffer* indexBuffer;			//순서 버퍼
	ID3D11InputLayout* inputLayout;		//입력 레이아웃 변수

	ID3D11Buffer* constantBuffer;		//상수 버퍼(월드 행렬)

	XMFLOAT3 position;					//메시 위치정보

};

