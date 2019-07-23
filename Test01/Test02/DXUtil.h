#pragma once

#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Memory
{
	template<class T>void SafeRelease(T&t)
	{
		if (t)
		{
			t->Release(); //DX 라이브러리 자원 해제
			t = NULL;
		}
	}

	template<class T>void SafeDelete(T&t)//객체 해제
	{
		if (t)
		{
			delete t;
			t = NULL;
		}
	}

	template<class T>void SafeDeleteArray(T&t)//배열 해제
	{
		if (t)
		{
			delete[] t;
			t = NULL;
		}
	}

}

bool IsError(HRESULT hr, LPCTSTR msg); //오류 확인용
