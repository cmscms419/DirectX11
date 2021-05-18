/*
	00 : 프레임워크와 윈도우 만들기
		프레임워크를 작성하여 클래스 구조로 뻐대를 세운다.
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