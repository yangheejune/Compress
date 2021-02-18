#include "pch.h"
#include <iostream>
#include "Compress.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DWORD dwRet = 0;
	Compress compress;

	// ����
	dwRet = compress.CompressFile(L"������ ���", L"���� ���ϸ��� ������ ��� + ���ϸ�.zip");
	if (0 != dwRet) {
		wprintf(L"Faile to compress error : %d\n", dwRet);
	}
	else {
		wprintf(L"Faile to compress success\n");
	}

	// ��������
	dwRet = compress.ExtractFile(L"���������� ���� ��� + ���ϸ�.zip", L"���������� ���� ������ ���");
	if (0 != dwRet) {
		wprintf(L"Faile to extract error : %d\n", dwRet);
	}
	else {
		wprintf(L"Faile to extract success\n");
	}
	   
}

