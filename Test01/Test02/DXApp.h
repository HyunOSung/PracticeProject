#pragma once
#include"AppWindow.h"
#include "DXUtil.h"

class DXApp
{
public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	virtual int Run() = 0; //���� ����ȭ, �����ο��� ����
	virtual bool Init(); //
	virtual void Update() = 0;
	virtual void Render() = 0;




protected:
	bool InitializeDX3D();
	void SetViewPort();


protected:
	AppWindow* window; //â ������

	ID3D11Device* device; //�� ���� ��ġ����
	ID3D11DeviceContext* deviceContext; // ������ ���ؽ�Ʈ����
	
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
};

