#include "DXUT.h"
#include "DXconvAnsiToWide.h"

DXconvAnsiToWide* DXconvAnsiToWide::SharedInstance ;

HRESULT DXconvAnsiToWide::Change( WCHAR* wstrDest, const CHAR* strSrc, int ct ) 
{
	if( wstrDest == NULL || strSrc == NULL || ct < MIN_STRING_NUM )
		return E_INVALIDARG ;

	int nResult = MultiByteToWideChar( CP_ACP, 0 , strSrc, -1, wstrDest, ct ) ;
	wstrDest[ct-1] = 0 ;

	if( nResult == 0 ) 
		return E_FAIL ;

	return S_OK ;
}