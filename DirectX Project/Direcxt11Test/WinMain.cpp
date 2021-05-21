/*
	01: DirectX 11 초기화
		DirectX 11 초기화하고 종료하는 방법과 창에 렌더링하는 방법
*/

#include "Stdafx.h"
#include "SystemClass.h"

#define MAX_LOADSTRING 100

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR IpCmdLine, _In_ int nCmdshow)
{

	// System 객체 생성
	SystemClass* System = new SystemClass;
	if (!System)
	{
		return -1;
	}

	// System 객체 초기화 및 실행
	if (System->Initialize())
	{
		System->Run();
	}

	// System 객체 종료 및 메모리 반환
	System->Shutdown();
	delete System;
	System = nullptr;


	return 0;
}