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
	//��������ȭ ���¸� �����մϴ�.
	m_vsync_enabled = vsync;

	//DirectX �׷��� �������̽� ���丮�� �����մϴ�.
	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
	{
		return false;
	}

	//���丮 ��ü�� ����Ͽ� ù��° �׷��� ī�� �������̽� ��͸� �����մϴ�.
	IDXGIAdapter* adapter = nullptr;
	if (FAILED(factory->EnumAdapters(0, &adapter)))
	{
		return false;
	}

	//���(�����)�� ���� ù��° ��͸� �����մϴ�.
	IDXGIOutput* adapterOutput = nullptr;
	if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
	{
		return false;
	}

	// ��� (�����)�� ���� DXGI_FORMAT_R8G8B8A8_UNORM ǥ�� ���Ŀ� �´� ��� ���� �����ɴϴ�.
	unsigned int numModes = 0;
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL)))
	{
		return false;
	}

	//������ ��� ����Ϳ� �׷���ī�� ������ ������ ����Ʈ�� �����մϴ�.
	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	if (displayModeList)
	{
		return false;
	}

	//���� ���÷��� ��忡 ���� ����Ʈ�� ä��ϴ�.
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList)))
	{
		return false;
	}

	// ���� ��� ���÷��� ��忡 ���� ȭ�� �ʺ�/���̿� �´� ���÷��� ��带 ã���ϴ�.
	// ������ ���� ã���� ������� ���ΰ�ħ ������ �и�� ���� ���� �����մϴ�.
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

	//����ī���� ����ü�� ����ϴ�.
	DXGI_ADAPTER_DESC adapterDesc;
	if (FAILED(adapter->GetDesc(&adapterDesc)))
	{
		return false;
	}

	//����ī�� �޸� �뷮 ������ �ް�����Ʈ ������ �����մϴ�.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// ���� ī���� �̸��� �����մϴ�.
	size_t stringLenghth = 0;
	if (wcstombs_s(&stringLenghth, m_videoCardDescription, 128, adapterDesc.Description, 128) != 0)
	{
		return false;
	}

	//���÷��� ��� ����Ʈ�� �����մϴ�.
	delete[] displayModeList;
	displayModeList = 0;

	//��� ��͸� �����մϴ�.
	adapter->Release();
	adapter = 0;

	//���丮 ��ü�� �����մϴ�.
	factory->Release();
	factory = 0;

	//SwapChain ����ü�� �ʱ�ȭ�մϴ�.
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//����۸� 1���� ����ϵ��� �����մϴ�.
	swapChainDesc.BufferCount = 1;

	//������� ���̿� ���̸� �����մϴ�.
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	//32vit �����̽��� �����մϴ�.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//������� ���ΰ�ħ ������ �����մϴ�.
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

	//������� ���뵵�� �����մϴ�.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//�������� ���� ������ �ڵ��� �����մϴ�.
	swapChainDesc.OutputWindow = hwnd;

	//��Ƽ���ø��� ���ϴ�.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;


	// â��� or Ǯ��ũ�� ��带 �����մϴ�.
	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// ��ĵ ���� ���� �� ũ�⸦ �������� �������� �����մϴ�.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//��µ� ���� ����۸� ��쵵�� �����մϴ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//�߰� �ɼ� �÷��׸� ������� �ʽ��ϴ�.
	swapChainDesc.Flags = 0;

	//��ó������ DirectX 11 �� �����դ���.
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	//SwapChain, Direct3D ��ġ �� Direct3D ��ġ ���ؽ�Ʈ�� ����ϴ�.
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1
		, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_devicecontext)))
	{
		return false;
	}

	//����� �����͸� ���ɴϴ�
	ID3D11Texture2D* backBufferPtr = nullptr;
	if (FAILED(m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView)))
	{
		return false;
	}

	//����� �����͸� �����մϴ�
	backBufferPtr->Release();
	backBufferPtr = 0;

	// ���� ���� ����ü�� �ʱ�ȭ�մϴ�
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));


}