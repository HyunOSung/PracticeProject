#pragma once
#include"AppWindow.h"
#include "DXUtil.h"

class DXApp
{
public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	virtual int Run() = 0; //순수 가상화, 엔진부에서 구현
	virtual bool Init(); //
	virtual void Update() = 0;
	virtual void Render() = 0;




protected:
	bool InitializeDX3D();
	void SetViewPort();


protected:
	AppWindow* window; //창 생성용

	ID3D11Device* device; //앱 생성 장치에서
	ID3D11DeviceContext* deviceContext; // 연동은 컨텍스트에서
	
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
};

