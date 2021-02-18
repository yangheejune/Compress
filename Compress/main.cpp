#include "pch.h"
#include <iostream>
#include "Compress.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DWORD dwRet = 0;
	Compress compress;

	// 압축
	dwRet = compress.CompressFile(L"압축할 경로", L"압축 파일명을 저장할 경로 + 파일명.zip");
	if (0 != dwRet) {
		wprintf(L"Faile to compress error : %d\n", dwRet);
	}
	else {
		wprintf(L"Faile to compress success\n");
	}

	// 압축해제
	dwRet = compress.ExtractFile(L"압축해제할 파일 경로 + 파일명.zip", L"압축해제한 파일 저장할 경로");
	if (0 != dwRet) {
		wprintf(L"Faile to extract error : %d\n", dwRet);
	}
	else {
		wprintf(L"Faile to extract success\n");
	}
	   
}

