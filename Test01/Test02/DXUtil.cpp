#include "DXUtil.h"

bool IsError(HRESULT hr, LPCTSTR msg)
{
	if (hr < 0)	//������ �ִٸ� �޼��� ���.
	{
		MessageBox(NULL, msg, TEXT("����"), MB_OK);
		return true;
	}
	return false;
}