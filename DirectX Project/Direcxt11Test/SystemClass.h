#pragma once

class InputClass;
class GraphicsClass;

//WinAPI 위도우 프로그래밍을 클래스화 한 것이다.
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


	//그래픽과 입력을 처리 할 두 객체
	InputClass* m_Input = nullptr;
	GraphicsClass* m_Graphics = nullptr;

};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* ApplicationHandle = 0;