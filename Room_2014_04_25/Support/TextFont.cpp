#include "DXUT.h"
#include "TextFont.h"

TextFont* TextFont::m_pTextFont ;
HRESULT DXconvAnsiToWideA(  WCHAR* wstrDest, const CHAR* strSrc, int ct ) ;


void TextFont::TextDraw(LPD3DXFONT _pFont, std::string _text, D3DXVECTOR3 _Pos )
{
	WCHAR TextBuff[255] = { 0 } ;
	DXconvAnsiToWideA( TextBuff, _text.c_str(), 255 ) ;
	RECT rect = {_Pos.x, _Pos.y, 0, 0 } ;

	_pFont->DrawText( NULL, TextBuff,-1,&rect,DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(255,255,255,255)) ;
}

HRESULT DXconvAnsiToWideA(  WCHAR* wstrDest, const CHAR* strSrc, int ct )
{
	// ˆø”‚Ì*‚ªNULL‚Ìê‡‚ÆA•¶š”‚ª1ˆÈ‰º‚Ìê‡‚ÍƒGƒ‰[
    if( wstrDest==NULL || strSrc==NULL || ct < 1 )
        return E_INVALIDARG;

    int nResult = MultiByteToWideChar( CP_ACP, 0, strSrc, -1, wstrDest, ct );
    wstrDest[ct-1] = 0;
    
    if( nResult == 0 )
        return E_FAIL;
    return S_OK;
}