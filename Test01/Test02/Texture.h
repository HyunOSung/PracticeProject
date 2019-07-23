#pragma once

#include "DXUtil.h"
#include"Library/DirectXTex.h"

#pragma comment(lib, "Library/DirectXTex.lib")

using namespace DirectX;

class Texture
{
public:
	Texture();
	~Texture();

	bool LoadTextureFromFile(ID3D11Device* device);
	void Release();

private:
	HRESULT GetScratchImage(LPCTSTR fileName, ScratchImage* image);

public:
	LPCTSTR fileName;
	ID3D11ShaderResourceView* textureResourceView;

};

