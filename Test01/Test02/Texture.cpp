#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

bool Texture::LoadTextureFromFile(ID3D11Device * device)
{
	ScratchImage image;
	HRESULT result = GetScratchImage(fileName, &image);
	if (IsError(result, TEXT("이미지 파일 로드 실패")))
	{
		return false;
	}

	ID3D11Texture2D* texture;
	result = CreateTexture(device, image.GetImages(), image.GetImageCount(), image.GetMetadata(), (ID3D11Resource**)&texture);
	if (IsError(result, TEXT("텍스쳐 리소스 생성 실패")))
	{
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	ZeroMemory(&viewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);

	viewDesc.Format = textureDesc.Format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MostDetailedMip = 0;
	viewDesc.Texture2D.MipLevels = 1;

	result = device->CreateShaderResourceView(texture, &viewDesc, &textureResourceView);
	if (IsError(result, TEXT("셰이더 리소스 뷰 생성 실패")))
	{
		return false;
	}

	Memory::SafeRelease(texture);


	return true;
}

void Texture::Release()
{
	Memory::SafeRelease(textureResourceView);
}

HRESULT Texture::GetScratchImage(LPCTSTR fileName, ScratchImage * image)
{
	TCHAR fileExtension[10];
	_wsplitpath_s(fileName, NULL, NULL, NULL, NULL, NULL, NULL, fileExtension, sizeof(fileExtension) / sizeof(LPCTSTR));

	if (wcscmp(fileExtension, TEXT(".tga")) == 0 || wcscmp(fileExtension, TEXT(".TGA")) == 0)
	{
		return LoadFromTGAFile(fileName, NULL, *image);
	}
	else if (wcscmp(fileExtension, TEXT(".dds")) == 0 || wcscmp(fileExtension, TEXT(".DDS")) == 0)
	{
		return LoadFromDDSFile(fileName, DDS_FLAGS_NONE, NULL, *image);
	}
	else
	{
		return LoadFromWICFile(fileName, WIC_FLAGS_NONE, NULL, *image);
	}

	return E_NOTIMPL;
}
