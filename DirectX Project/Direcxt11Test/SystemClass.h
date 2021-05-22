#pragma once

class InputClass;
class GraphicsClass;

//WinAPI ������ ���α׷����� Ŭ����ȭ �� ���̴�.
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applocationName = NULL;
	HINSTANCE m_hinstance = NULL;
	HWND m_hwnd = NULL;


	//�׷��Ȱ� �Է��� ó�� �� �� ��ü
	InputClass* m_Input = nullptr;
	GraphicsClass* m_Graphics = nullptr;

};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* ApplicationHandle = 0;