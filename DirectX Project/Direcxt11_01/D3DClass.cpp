#include "Stdafx.h"
#include "d3dclass.h"

D3DClass::D3DClass()
{

}

D3DClass::D3DClass(const D3DClass& other)
{

}

D3DClass::~D3DClass()
{

}

bool D3DClass::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear)
{
	//수직도기화 상태를 저장합니다.
	m_vsync_enabled = vsync;

	//DirectX 그래픽 인터페이스 팩토리를 생성합니다.
	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
	{
		return false;
	}

	//팩토리 객체를 사용하여 첫번째 그래픽 카드 인터페이스 어뎁터를 생성합니다.
	IDXGIAdapter* adapter = nullptr;
	if (FAILED(factory->EnumAdapters(0, &adapter)))
	{
		return false;
	}

	//출력(모니터)에 대한 첫번째 어뎁터를 지정합니다.
	IDXGIOutput* adapterOutput = nullptr;
	if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
	{
		return false;
	}

	// 출력 (모니터)에 대한 DXGI_FORMAT_R8G8B8A8_UNORM 표시 형식에 맞는 모드 수를 가져옵니다.
	unsigned int numModes = 0;
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL)))
	{
		return false;
	}

	//가능한 모든 모니터와 그래픽카드 조합을 저장할 리스트를 생성합니다.
	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	if (displayModeList)
	{
		return false;
	}

	//이제 디스플레이 모드에 대한 리스트를 채웁니다.
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList)))
	{
		return false;
	}

	// 이제 모든 디스플레이 모드에 대해 화면 너비/높이에 맞는 디스플레이 모드를 찾습니다.
	// 적합한 것을 찾으면 모니터의 새로고침 비율의 분모와 분자 값을 저장합니다.
	unsigned int numerator = 0;
	unsigned int denominator = 0;
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)screenHeight)
		{
			if (displayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	//비디오카드의 구조체를 얻습니다.
	DXGI_ADAPTER_DESC adapterDesc;
	if (FAILED(adapter->GetDesc(&adapterDesc)))
	{
		return false;
	}

	//비디오카드 메모리 용량 단위를 메가바이트 단위로 저장합니다.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// 비디오 카드의 이름을 저장합니다.
	size_t stringLenghth = 0;
	if (wcstombs_s(&stringLenghth, m_videoCardDescription, 128, adapterDesc.Description, 128) != 0)
	{
		return false;
	}

	//디스플레이 모드 리스트를 해제합니다.
	delete[] displayModeList;
	displayModeList = 0;

	//출력 어뎁터를 해제합니다.
	adapter->Release();
	adapter = 0;

	//팩토리 객체를 해제합니다.
	factory->Release();
	factory = 0;

	//SwapChain 구조체를 초기화합니다.
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//백버퍼를 1개만 사용하도록 지정합니다.
	swapChainDesc.BufferCount = 1;

	//백버퍼의 넓이와 높이를 지정합니다.
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	//32vit 서페이스를 설정합니다.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//백버퍼의 새로고침 비율을 설정합니다.
	if (m_vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	//백버퍼의 사용용도를 지정합니다.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//랜더링에 사용될 윈도우 핸들을 지정합니다.
	swapChainDesc.OutputWindow = hwnd;

	//멀티샘플링을 끕니다.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;


	// 창모드 or 풀슼크린 모드를 설정합니다.
	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// 스캔 라인 순서 및 크기를 지정하지 않음으로 설정합니다.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//출력된 다음 백버퍼를 비우도록 지정합니다
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//추가 옵션 플래그를 사용하지 않습니다.
	swapChainDesc.Flags = 0;

	//피처레벨을 DirectX 11 로 설정합ㄴ디ㅏ.
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	//SwapChain, Direct3D 장치 및 Direct3D 장치 컨텍스트를 만듭니다.
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1
		, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_devicecontext)))
	{
		return false;
	}

	//백버퍼 포인터를 얻어옵니다
	ID3D11Texture2D* backBufferPtr = nullptr;
	if (FAILED(m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView)))
	{
		return false;
	}

	//백버퍼 포인터를 해제합니다
	backBufferPtr->Release();
	backBufferPtr = 0;

	// 깊이 버퍼 구조체를 초기화합니다
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));


}