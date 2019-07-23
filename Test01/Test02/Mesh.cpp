#include "Mesh.h"



Mesh::Mesh()
{
}

Mesh::Mesh(float x, float y, float z)
{
	SetPosition(x, y, z);
}


Mesh::~Mesh()
{
	Memory::SafeRelease(vertexBuffer);
	Memory::SafeRelease(inputLayout);
}

bool Mesh::InitializeBuffers(ID3D11Device * device, ID3DBlob * vertexShaderBuffer)
{
	Vertex vertices[] = {
		Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)/*, XMFLOAT2(1.0f, 0.0f)*/),
		Vertex(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)/*, XMFLOAT2(1.0f, 1.0f)*/),
		Vertex(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)/*, XMFLOAT2(0.0f, 1.0f)*/),
		Vertex(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)/*, XMFLOAT2(0.0f, 0.0f)*/),
		Vertex(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)/*, XMFLOAT2(1.0f, 0.0f)*/),
		Vertex(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)/*, XMFLOAT2(1.0f, 1.0f)*/),
		Vertex(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)/*, XMFLOAT2(0.0f, 1.0f)*/),
		Vertex(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)/*, XMFLOAT2(0.0f, 0.0f)*/)
	};	//왼손 좌표계, 정점 위치 정보, 정점 색상 정보

	nVertices = ARRAYSIZE(vertices);
	D3D11_BUFFER_DESC vbDesc;	//버텍스 정보 서술자
	ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
	vbDesc.ByteWidth = sizeof(Vertex) * nVertices;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.MiscFlags = 0;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;


	//정점 배열 정보를 넣어줄 구조체
	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
	vbData.pSysMem = vertices;

	//정점 버퍼 생성.
	HRESULT result = device->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);
	if (IsError(result, TEXT("정점 버퍼 생성 실패")))
	{
		return false;
	}

	DWORD indices[] =
	{
		0,1,2,
		0,2,3,

		0,1,5,
		0,4,5,

		4,5,6,
		4,6,7,

		0,3,4,
		3,4,7,

		2,3,6,
		3,6,7,

		1,2,5,
		2,5,6

	};

	nIndices = ARRAYSIZE(indices);

	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(D3D11_BUFFER_DESC));
	ibDesc.ByteWidth = sizeof(DWORD) * nIndices;  //DWORD CPU가 처리할 값 범위, 인덱스 개수 만큼 대입
	ibDesc.CPUAccessFlags = 0;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.MiscFlags = 0;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA ibData;
	ZeroMemory(&ibData, sizeof(D3D11_SUBRESOURCE_DATA));
	ibData.pSysMem = indices; //시스템 멤버라고 선언

	result = device->CreateBuffer(&ibDesc, &ibData, &indexBuffer);
	if (IsError(result, TEXT("인덱스 버퍼 생성 실패")))
	{
		return false;
	}


	//입력 레이아웃 서술자 생성.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA},
		//{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA},
	};

	//입력 레이아웃 생성.
	result = device->CreateInputLayout(layout, ARRAYSIZE(layout),
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		&inputLayout);
	if (IsError(result, TEXT("입력 레이아웃 생성 실패")))
	{
		return false;
	}

	PerObjectBuffer matrixData;
	matrixData.world = XMMatrixTranspose(GetWorldMatrix());

	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.ByteWidth = sizeof(PerObjectBuffer);
	cbDesc.CPUAccessFlags = 0;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.MiscFlags = 0;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA cbData;
	ZeroMemory(&cbData, sizeof(D3D11_SUBRESOURCE_DATA));
	cbData.pSysMem = &matrixData;

	result = device->CreateBuffer(&cbDesc, &cbData, &constantBuffer);
	if (IsError(result, TEXT("오브젝트 버퍼 생성 실패")))
	{
		return false;
	}


	return true;
}

void Mesh::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	//정점 버퍼 전달
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);	//IA -> InputAssembly

	//인덱스 버퍼 바인딩
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//입력 레이아웃 전달
	deviceContext->IASetInputLayout(inputLayout);

	//위상 설정.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//그림 그리는 방법(점, 선, 면 등)

	//그리기
	deviceContext->DrawIndexed(nIndices, 0, 0);	//이전에 버텍스에서 그리던 방식으로 인덱스 버퍼에 따르게 변경

}

void Mesh::Update(ID3D11DeviceContext * deviceContext)
{
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
}

XMMATRIX Mesh::GetWorldMatrix() const
{
	return XMMatrixTranslation(position.x, position.y, position.z);
}
