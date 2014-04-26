//	char�^��wide_char�^�ɕϊ����邽�߂����̃N���X

#pragma once
#include "DXUT.h"

class DXconvAnsiToWide
{
private:
	enum
	{
		MIN_STRING_NUM = 1 
	} ;

	static DXconvAnsiToWide* SharedInstance ;

	DXconvAnsiToWide(){};
	~DXconvAnsiToWide(){};

	DXconvAnsiToWide( const DXconvAnsiToWide &obj ) ;
	DXconvAnsiToWide& operator = ( const DXconvAnsiToWide &obj ) ;

public:
	inline static DXconvAnsiToWide* GetInstance()
	{
		if( !SharedInstance ) SharedInstance = new DXconvAnsiToWide() ;
		return SharedInstance ;
	};
	
	inline static void DeleteInstance()
	{
		SAFE_DELETE( SharedInstance ) ;
	};

	static HRESULT Change( WCHAR* wstrDest, const CHAR* strSrc, int ct ) ;
};

