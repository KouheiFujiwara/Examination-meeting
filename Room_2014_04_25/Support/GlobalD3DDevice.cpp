#include "DXUT.h"
#include "GlobalD3DDevice.h"

GlobalD3DDevice*	GlobalD3DDevice::SharedInstance ;
IDirect3DDevice9*	GlobalD3DDevice::m_pd3dDevice ;
HWND				GlobalD3DDevice::m_hWnd ;