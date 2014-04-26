//	Ç∑Ç◊ÇƒÇÃIDirect3DDevice9 ÇÃïœêîÇìùàÍ

#pragma once
#include "DXUT.h"

class GlobalD3DDevice
{
private:

	static GlobalD3DDevice* SharedInstance ;

	GlobalD3DDevice(){};
	~GlobalD3DDevice(){};

	GlobalD3DDevice( const GlobalD3DDevice &obj ) ;
	GlobalD3DDevice& operator = ( const GlobalD3DDevice &obj ) ;

public:
	static IDirect3DDevice9 *m_pd3dDevice ;
	static HWND m_hWnd ;

	inline static GlobalD3DDevice* GetInstance( IDirect3DDevice9 *_pd3dDevice ) 
	{
		if( !SharedInstance ){ 
			SharedInstance = new GlobalD3DDevice() ;
			m_pd3dDevice = _pd3dDevice ;
		}
		return SharedInstance ;
	}; 

	inline static void DeleteInstance() 
	{
		SAFE_DELETE( SharedInstance ) ;
	}
};

