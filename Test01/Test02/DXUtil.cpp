#include "DXUtil.h"

bool IsError(HRESULT hr, LPCTSTR msg)
{
	if (hr < 0)	//오류가 있다면 메세지 출력.
	{
		MessageBox(NULL, msg, TEXT("오류"), MB_OK);
		return true;
	}
	return false;
}