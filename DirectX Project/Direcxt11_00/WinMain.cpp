/*
	00 : �����ӿ�ũ�� ������ �����
		�����ӿ�ũ�� �ۼ��Ͽ� Ŭ���� ������ ���븦 �����.
*/

#include "Stdafx.h"
#include "SystemClass.h"

#define MAX_LOADSTRING 100

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR IpCmdLine, _In_ int nCmdshow)
{

	// System ��ü ����
	SystemClass* System = new SystemClass;
	if (!System)
	{
		return -1;
	}

	// System ��ü �ʱ�ȭ �� ����
	if (System->Initialize())
	{
		System->Run();
	}

	// System ��ü ���� �� �޸� ��ȯ
	System->Shutdown();
	delete System;
	System = nullptr;


	return 0;
}