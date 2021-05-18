#include "Stdafx.h"
#include "d3dclass.h"
#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{

}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}

GraphicsClass::~GraphicsClass()
{

}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	//Direct3D °´Ã¼ »ý¼º
	m_Direct3D = (D3DClass*)_aligned_malloc(sizeof(D3DClass), 16);

	return true;
}

void GraphicsClass::Shutdown()
{

}

bool GraphicsClass::Frame()
{
	return true;
}

bool GraphicsClass::Render()
{
	return true;
}